.PHONY: gpu-hello
gpu-hello:
	./build/HSAIL_X86/gem5.debug --debug-flags=RubySlicc --stats-file=gpu-hello.stats --outdir=gpu-hello ./configs/example/apu_se.py -u 4 -c ./tests/test-progs/gpu-hello/bin/x86/linux/gpu-hello --TCC_latency 24 --bw-scalor 1 -k ./tests/test-progs/gpu-hello/bin/x86/linux/gpu-hello-kernel.asm

.PHONY: viper
viper:
	scons PROTOCOL=GPU_VIPER build/HSAIL_X86/gem5.debug

.PHONY: bench
bench:
	./build/HSAIL_X86/gem5.debug  --stats-file=bench.stats --outdir=benchmark ./configs/example/apu_se.py -u 8 -c ../pagerank_mat_u8 -k ../kernel.b4.asm 
