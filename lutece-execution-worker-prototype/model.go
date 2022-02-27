package main

import (
	"os"

	"github.com/opencontainers/runc/libcontainer"
	"github.com/opencontainers/runc/libcontainer/configs"
	"golang.org/x/sys/unix"
)

type FileDescriptor struct {
	Name      string  `json:"name"`
	IsNewFile bool    `json:"is_new_file"`
	Bucket    *string `json:"bucket,omitempty"`
	MaxSize   *int32  `json:"max_size,omitempty"`
}

type Resources struct { // Just a basic version
	CPUs   int32 `json:"cpus"`
	Memory int32 `json:"memory"`
}

type ProcessLimits struct {
	TimeLimit   int32  `json:"time_limit"`
	MemoryLimit int32  `json:"mem_limit"`
	StackLimit  *int32 `json:"stack_limit,omitempty"`
}

type Phase struct {
	RunArgs   []string      `json:"run_args"`
	Env       []string      `json:"env"`
	Resources Resources     `json:"resources"`
	Limits    ProcessLimits `json:"limits"`
}

type ExecRequest struct {
	Phases []Phase `json:"phases"`
}

type ProcessResult struct {
	State *os.ProcessState
	Err   error
}

type ProcessEnv struct {
	Container   libcontainer.Container
	RunArgs     []string
	TimeLimit   int64
	MemoryLimit int64
	StackLimit  *int64
	WorkDir     string
	Input       *os.File
	Output      *os.File
	ErrFile     *os.File
}

func (p *ProcessEnv) Destroy() {
	p.Container.Destroy()
}

func (p *ProcessEnv) Run(process *libcontainer.Process) error {
	return p.Container.Run(process)
}

func (p *ProcessEnv) NotifyOOM() (<-chan struct{}, error) {
	return p.Container.NotifyOOM()
}

func (p *ProcessEnv) Process() *libcontainer.Process {
	stackLimit := p.MemoryLimit
	if p.StackLimit != nil {
		stackLimit = *p.StackLimit
	}
	return &libcontainer.Process{
		Args:             p.RunArgs,
		Env:              []string{"PATH=/bin"},
		User:             "test",
		AdditionalGroups: []string{},
		Cwd:              p.WorkDir,
		Stdin:            p.Input,
		Stdout:           p.Output,
		Stderr:           p.ErrFile,
		ExtraFiles:       []*os.File{},
		ConsoleWidth:     0,
		ConsoleHeight:    0,
		Capabilities:     &configs.Capabilities{},
		AppArmorProfile:  "",
		Label:            "",
		NoNewPrivileges:  new(bool),
		Rlimits: []configs.Rlimit{
			{
				Type: unix.RLIMIT_STACK,
				Hard: uint64(stackLimit),
				Soft: uint64(stackLimit),
			},
		},
		ConsoleSocket: &os.File{},
		Init:          true,
		LogLevel:      "",
	}
}
