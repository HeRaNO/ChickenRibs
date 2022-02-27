package main

func executeSingle(env *ProcessEnv) (*ProcessResult, error) {
	defer env.Destroy()
	process := env.Process()
	processFinished := make(chan struct{})
	defer close(processFinished)
	errChan := make(chan error)
	defer close(errChan)
	chOOM, err := env.NotifyOOM()
	if err != nil {
		return nil, err
	}

	go RunDaemon(process, GetWallTimeLimit(env.TimeLimit), processFinished, chOOM, errChan)

	err = env.Run(process)
	if err != nil {
		processFinished <- struct{}{}
		return nil, err
	}

	p, err := process.Wait()
	processFinished <- struct{}{} // Should always use this to kill the daemon goroutine
	if err != nil {
		return &ProcessResult{
			State: p,
			Err:   err,
		}, nil
	}
	return &ProcessResult{
		State: p,
		Err:   <-errChan,
	}, nil
}
