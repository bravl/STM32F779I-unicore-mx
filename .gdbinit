tar ext:3333
monitor halt
file STM_Eval.elf
load STM_Eval.elf
monitor reset halt
mon arm semihosting enable
