package main

import (
	"flag"
	"fmt"
	"loadbalancer/algorithms"
	"loadbalancer/client"
	"loadbalancer/loadbalancer"
	"loadbalancer/server"
	"math/rand"
	"sync"
	"time"
)

var servers []*server.Server

func main() {
	// Lees command line argumenten voor aantal clients, servers, etc
	numClients := flag.Int("clients", 10, "Number of clients")
	numServers := flag.Int("servers", 3, "Number of servers")
	algorithmType := flag.String("algorithm", "rr", "Load balancing algorithm: rr (Round Robin), wrr (Weighted Round Robin), lc (Least Connections)")
	testDuration := flag.Int("duration", 30, "Test duration in seconds")
	flag.Parse()

	rand.Seed(time.Now().UnixNano())

	fmt.Printf("Starting Load Balancer Test\n")
	fmt.Printf("Clients: %d, Servers: %d, Algorithm: %s, Duration: %ds\n\n",
		*numClients, *numServers, *algorithmType, *testDuration)

	// Maak alle servers aan en start ze in aparte goroutines
	// Elke server krijgt een eigen poort (8081, 8082, etc)
	servers = make([]*server.Server, *numServers)
	serverAddresses := make([]string, *numServers)
	weights := make([]int, *numServers)

	for i := 0; i < *numServers; i++ {
		port := 8081 + i
		weight := i + 1 // gewicht voor weighted round robin (server 0=1, server 1=2, etc)
		servers[i] = server.New(i, port, weight)
		serverAddresses[i] = servers[i].GetAddress()
		weights[i] = weight

		go servers[i].Start()
	}

	time.Sleep(1 * time.Second) // wacht tot servers klaar zijn

	// Kies het juiste load balancing algoritme op basis van de flag
	var algo algorithms.Algorithm
	switch *algorithmType {
	case "rr":
		algo = algorithms.NewRoundRobin(*numServers)
	case "wrr":
		algo = algorithms.NewWeightedRoundRobin(weights)
	case "lc":
		// least connections heeft een functie nodig om het aantal connecties op te halen
		algo = algorithms.NewLeastConnections(*numServers, func(idx int) int32 {
			return servers[idx].GetActiveConnections()
		})
	default:
		fmt.Printf("Unknown algorithm: %s, using Round Robin\n", *algorithmType)
		algo = algorithms.NewRoundRobin(*numServers)
	}

	// Start de load balancer op poort 8080
	lb := loadbalancer.New(algo, serverAddresses)
	go lb.Start(8080)

	time.Sleep(1 * time.Second) // wacht tot load balancer klaar is

	// Maak alle clients aan en laat ze requests sturen
	// WaitGroup zorgt ervoor dat we wachten tot alle clients klaar zijn
	clients := make([]*client.Client, *numClients)
	var wg sync.WaitGroup

	for i := 0; i < *numClients; i++ {
		clients[i] = client.New(i, "http://localhost:8080")
		wg.Add(1)
		go clients[i].Start(time.Duration(*testDuration)*time.Second, &wg)
	}

	wg.Wait() // wacht tot alle clients klaar zijn met testen

	// Print de resultaten
	fmt.Println("\n=== Test Results ===")
	fmt.Printf("Algorithm: %s\n", algo.Name())
	fmt.Printf("Clients: %d, Servers: %d\n", *numClients, *numServers)
	fmt.Printf("Duration: %d seconds\n\n", *testDuration)

	// Verzamel statistieken van alle clients
	totalRequests := 0
	totalPerformance := 0.0

	for i, c := range clients {
		requests, performance := c.GetStats()
		avgPerf := c.GetAveragePerformance()
		totalRequests += requests
		totalPerformance += performance
		fmt.Printf("Client %d: %d requests, avg performance: %.4f seconds\n",
			i, requests, avgPerf)
	}

	// Bereken overall performance (= response tijd - wachttijd)
	overallAvgPerformance := totalPerformance / float64(totalRequests)
	fmt.Printf("\nTotal requests: %d\n", totalRequests)
	fmt.Printf("Overall average performance: %.4f seconds\n", overallAvgPerformance)
	fmt.Printf("Throughput: %.2f requests/second\n", float64(totalRequests)/float64(*testDuration))

	// Laat zien hoeveel connecties elke server nog heeft
	fmt.Println("\n=== Server Statistics ===")
	for i, s := range servers {
		fmt.Printf("Server %d (weight %d): %d active connections\n",
			i, s.Weight, s.GetActiveConnections())
	}
}
