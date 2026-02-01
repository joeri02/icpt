package algorithms

import (
	"sync"
	"sync/atomic"
)

type Algorithm interface {
	GetNext() int
	Name() string
}

type RoundRobin struct {
	curr uint64
	num_servers int
}

func NewRoundRobin(numServers int) *RoundRobin {
	return &RoundRobin{
		curr: 0,
		num_servers: numServers,
	}
}

func (rr *RoundRobin) GetNext() int {
	n := atomic.AddUint64(&rr.curr, 1)
	return int((n - 1) % uint64(rr.num_servers))
}

func (rr *RoundRobin) Name() string {
	return "Round Robin"
}

// Weighted Round Robin Algorithm
type WeightedRoundRobin struct {
	weights      []int
	currentIndex int
	currentWeight int
	maxWeight    int
	gcd          int
	mu           sync.Mutex
}

func NewWeightedRoundRobin(weights []int) *WeightedRoundRobin {
	maxW := 0
	gcdVal := weights[0]

	for _, w := range weights {
		if w > maxW {
			maxW = w
		}
		gcdVal = gcd(gcdVal, w)
	}

	return &WeightedRoundRobin{
		weights:      weights,
		currentIndex: -1,
		currentWeight: 0,
		maxWeight:    maxW,
		gcd:          gcdVal,
	}
}

func (wrr *WeightedRoundRobin) GetNext() int {
	wrr.mu.Lock()
	defer wrr.mu.Unlock()

	for {
		wrr.currentIndex = (wrr.currentIndex + 1) % len(wrr.weights)
		if wrr.currentIndex == 0 {
			wrr.currentWeight = wrr.currentWeight - wrr.gcd
			if wrr.currentWeight <= 0 {
				wrr.currentWeight = wrr.maxWeight
			}
		}
		if wrr.weights[wrr.currentIndex] >= wrr.currentWeight {
			return wrr.currentIndex
		}
	}
}

func (wrr *WeightedRoundRobin) Name() string {
	return "Weighted Round Robin"
}

// GCD helper function
func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

// Least Connections Algorithm
type LeastConnections struct {
	getConnections func(int) int32
	servers        int
	mu             sync.Mutex
}

func NewLeastConnections(numServers int, getConnFunc func(int) int32) *LeastConnections {
	return &LeastConnections{
		getConnections: getConnFunc,
		servers:        numServers,
	}
}

func (lc *LeastConnections) GetNext() int {
	lc.mu.Lock()
	defer lc.mu.Unlock()

	minConnections := int32(^uint32(0) >> 1) // Max int32
	selectedServer := 0

	for i := 0; i < lc.servers; i++ {
		connections := lc.getConnections(i)
		if connections < minConnections {
			minConnections = connections
			selectedServer = i
		}
	}

	return selectedServer
}

func (lc *LeastConnections) Name() string {
	return "Least Connections"
}
