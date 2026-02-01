package client

import (
	"fmt"
	"math/rand"
	"net/http"
	"sync"
	"time"
)

type Client struct {
	ID                int
	LoadBalancerURL   string
	TotalRequests     int
	TotalPerformance  float64
	mu                sync.Mutex
}

func New(id int, lbURL string) *Client {
	return &Client{
		ID:              id,
		LoadBalancerURL: lbURL,
	}
}

func (c *Client) Start(duration time.Duration, wg *sync.WaitGroup) {
	defer wg.Done()

	startTime := time.Now()
	for time.Since(startTime) < duration {
		c.sendRequest()
	}
}

func (c *Client) sendRequest() {
	// Generate random wait time between 0 and 1
	waitTime := rand.Float64()

	requestStart := time.Now()

	// Send HTTP request with wait time as parameter
	url := fmt.Sprintf("%s?wait=%.3f", c.LoadBalancerURL, waitTime)
	resp, err := http.Get(url)
	if err != nil {
		fmt.Printf("Client %d: Error sending request: %v\n", c.ID, err)
		return
	}
	defer resp.Body.Close()

	totalTime := time.Since(requestStart).Seconds()

	// Calculate performance: total time - wait time
	performance := totalTime - waitTime

	c.mu.Lock()
	c.TotalRequests++
	c.TotalPerformance += performance
	c.mu.Unlock()
}

func (c *Client) GetAveragePerformance() float64 {
	c.mu.Lock()
	defer c.mu.Unlock()

	if c.TotalRequests == 0 {
		return 0
	}
	return c.TotalPerformance / float64(c.TotalRequests)
}

func (c *Client) GetStats() (int, float64) {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.TotalRequests, c.TotalPerformance
}
