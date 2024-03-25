package redis

import (
	"context"
	"fmt"
	"time"

	"github.com/redis/go-redis/v9"
)

type redisMutex struct {
	client     *redis.Client
	key        string
	timeout    time.Duration
	timewait   time.Duration
	maxRetries int
	locked     bool
}

func newRedisMutex(cli *redis.Client, key string, timeout int, timewait int, retry int) *redisMutex {
	return &redisMutex{
		client:     cli,
		key:        fmt.Sprintf("mutex:%s", key),
		timeout:    time.Duration(timeout) * time.Second,
		timewait:   time.Duration(timewait) * time.Millisecond,
		maxRetries: retry,
		locked:     false,
	}
}

func (m *redisMutex) lock(ctx context.Context) bool {
	retryTime := 0
	for !m.locked {
		m.locked, _ = m.client.SetNX(ctx, m.key, 1, m.timeout).Result()
		if m.locked {
			break
		}
		retryTime++
		if retryTime > m.maxRetries {
			ttl, _ := m.client.TTL(ctx, m.key).Result()
			if ttl.String() == "-1s" {
				m.client.Del(ctx, m.key)
			}
			break
		}
		time.Sleep(m.timewait)
	}

	return m.locked
}

func (m *redisMutex) unlock(ctx context.Context) {
	if !m.locked {
		return
	}
	m.client.Del(ctx, m.key)
}
