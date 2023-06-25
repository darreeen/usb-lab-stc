SRCS=main timer utils usb/utils usb/power usb/usb usb/pipe_control/desc usb/pipe_control/handler usb/pipe_control/req_class usb/pipe_control/req_std usb/pipe_control/req_vendor usb/pipe_control/transaction usb/pipe_interrupt/transaction

OUT=usb-hid-lab
OBJS=$(foreach n,$(SRCS),$(n).rel)

CC=sdcc
LD=sdcc

CFLAGS=-c
AFLAGS=-c
LDFLAGS=
ALL = $(OUT).hex

all:	$(ALL)

$(OUT).hex: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(OUT).hex

%.rel:	%.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -f $(foreach n,$(SRCS),$(n).rel $(n).asm $(n).hex $(n).ihx $(n).lk $(n).lst $(n).map $(n).mem $(n).rst $(n).sym)
	# rm *.asm *.hex *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym
