package loadbalancer

import (
	"fmt"
	"io"
	"loadbalancer/algorithms"
	"net/http"
	"sync"
)

type LoadBalancer struct {
	Algorithm algorithms.Algorithm
	Servers   []string
	mu        sync.Mutex
}

func New(algorithm algorithms.Algorithm, servers []string) *LoadBalancer {
	return &LoadBalancer{
		Algorithm: algorithm,
		Servers:   servers,
	}
}

func (lb *LoadBalancer) Start(port int) {
	mux := http.NewServeMux()
	mux.HandleFunc("/", lb.handleRequest)
	addr := fmt.Sprintf(":%d", port)
	fmt.Printf("Load Balancer started on port %d using %s algorithm\n", port, lb.Algorithm.Name())
	http.ListenAndServe(addr, mux)
}

func (lb *LoadBalancer) handleRequest(w http.ResponseWriter, r *http.Request) {
	// Get next server using the algorithm
	serverIndex := lb.Algorithm.GetNext()
	serverURL := lb.Servers[serverIndex]

	// Forward the request to the selected server
	targetURL := fmt.Sprintf("%s%s", serverURL, r.URL.String())

	resp, err := http.Get(targetURL)
	if err != nil {
		http.Error(w, fmt.Sprintf("Error forwarding request: %v", err), http.StatusBadGateway)
		return
	}
	defer resp.Body.Close()

	// Copy response back to client
	w.WriteHeader(resp.StatusCode)
	io.Copy(w, resp.Body)
}
