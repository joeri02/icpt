package server

import (
	"fmt"
	"net/http"
	"strconv"
	"sync/atomic"
	"time"
)

type Server struct {
	ID              int
	Port            int
	ActiveConnections int32
	Weight          int
}

func New(id, port, weight int) *Server {
	return &Server{
		ID:     id,
		Port:   port,
		Weight: weight,
	}
}

func (s *Server) Start() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", s.handleRequest)
	addr := fmt.Sprintf(":%d", s.Port)
	fmt.Printf("Server %d started on port %d (weight: %d)\n", s.ID, s.Port, s.Weight)
	http.ListenAndServe(addr, mux)
}

func (s *Server) handleRequest(w http.ResponseWriter, r *http.Request) {
	atomic.AddInt32(&s.ActiveConnections, 1)
	defer atomic.AddInt32(&s.ActiveConnections, -1)

	// Get wait time from query parameter
	waitTimeStr := r.URL.Query().Get("wait")
	waitTime, err := strconv.ParseFloat(waitTimeStr, 64)
	if err != nil {
		waitTime = 0
	}

	// Simulate processing time
	time.Sleep(time.Duration(waitTime * float64(time.Second)))

	w.WriteHeader(http.StatusOK)
	fmt.Fprintf(w, "OK from Server %d", s.ID)
}

func (s *Server) GetActiveConnections() int32 {
	return atomic.LoadInt32(&s.ActiveConnections)
}

func (s *Server) GetAddress() string {
	return fmt.Sprintf("http://localhost:%d", s.Port)
}
