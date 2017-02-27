#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>

#define MOUSE_EVENT "/dev/input/event11"
#define KEYBOARD_EVENT "/dev/input/event12"

int keyboardfd;
int mousefd;

void send_keyboard_event(struct timeval time, int type, int code, int value)
{
	struct input_event event;
	event.time = time;
	event.type = type;
	event.code = code;
	event.value = value;
	write(keyboardfd, &event, sizeof(event));
}

int main(void)
{
	struct input_event event;
	if ((mousefd = open(MOUSE_EVENT, O_RDWR)) < 0) {
		puts("MOUSE_EVENT ERROR");
		return(EXIT_FAILURE);
	}
	if ((keyboardfd = open(KEYBOARD_EVENT, O_RDWR)) < 0) {
		puts("KEYBOARD_EVENT ERROR");
		return(EXIT_FAILURE);
	}
	
	while (1) {
		if (read(mousefd, &event, sizeof(event)) != sizeof(event)) {
			puts("ERROR");
			exit(EXIT_FAILURE);
		}
		switch(event.type) {
			case EV_KEY:
				//printf("EV_KEY code:%x, value:%x\n", event.code, event.value);
				switch(event.code) {
					case BTN_LEFT:
							send_keyboard_event(event.time, EV_KEY, KEY_C, 1);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							send_keyboard_event(event.time, EV_KEY, KEY_C, 0);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							break;
				}
				break;
			case EV_REL:
				if (event.code == REL_WHEEL) {
					//printf("EV_REL code:%x, value:%x\n", event.code, event.value);
					switch(event.value) {
						case 1:
							// puts("up");
							send_keyboard_event(event.time, EV_KEY, KEY_EQUAL, 1);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							send_keyboard_event(event.time, EV_KEY, KEY_EQUAL, 0);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							break;
						case -1:
							// puts("down");
							send_keyboard_event(event.time, EV_KEY, KEY_MINUS, 1);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							send_keyboard_event(event.time, EV_KEY, KEY_MINUS, 0);
							send_keyboard_event(event.time, EV_SYN, SYN_REPORT, 0);
							break;
					}
				}
				break;
			case EV_ABS:
				//printf("EV_ABS code:%x, value:%x\n", event.code, event.value);
				break;
		}
	}
  
	close(keyboardfd);
	close(mousefd);

	return(EXIT_SUCCESS);
}
