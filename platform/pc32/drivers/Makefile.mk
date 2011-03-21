DRIVERS := $(BSP)/drivers

# FIXME: $(BSP-MODULES) must be generated by 'make genconf'. And put into
#	 the $(CONF). We may include it.
BSP-MODULES := $(DRIVERS)/%.c

drv-cfile := $(wildcard $(DRIVERS)/*.c)
drv-ofile := $(drv-cfile:.c=.o)
drv-ofile := $(subst $(DRIVERS)/,$(BSP_OBJ)/,$(drv-ofile))

bsp-ofile += $(drv-ofile)

$(BSP_OBJ)/%.o : $(DRIVERS)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(BSP_CFLAGS) -c -o $@ $<
