#include <linux/input-event-codes.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int DoNotPrintUnkown = 0;
  
  if (argc != 2) {
    printf("USAGE: %s <path-to-event-file>\n", argv[0]);
    return -1;
  }

  char *eventfile = argv[1];

  int fd = open(eventfile, O_RDONLY, 0);
  
  if (fd == -1) {
    perror("open");
    return -1;
  }
  
  struct input_event inputevent;

  while (1) {
    read(fd, &inputevent, sizeof(inputevent));

    if (inputevent.type != EV_KEY || inputevent.value != 1) 
      continue;

    
    else if (inputevent.value == 2 || inputevent.value == 28) 
      continue;
    

    if (inputevent.code == KEY_BACKSPACE) {
      printf("Key pressed: Backspace\n");
      DoNotPrintUnkown = 1;
    }

    if (inputevent.code == 57) {
      printf(" ");
      DoNotPrintUnkown = 1; // I made sure it doesn't print "Unknown key" for this part also
    }

    if (inputevent.code >= KEY_1 && inputevent.code <= KEY_9) {
      int value = inputevent.code - 1;
      printf("Number pressed: %d\n", value);
      DoNotPrintUnkown = 1; // This variable does not allow printing "Unknown key"
    }

    
    switch (inputevent.code) {
      case KEY_A: printf("a"); break;
      case KEY_B: printf("b"); break;
      case KEY_C: printf("c"); break;
      case KEY_D: printf("d"); break;
      case KEY_E: printf("e"); break;
      case KEY_F: printf("f"); break;
      case KEY_G: printf("g"); break;
      case KEY_H: printf("h"); break;
      case KEY_I: printf("i"); break;
      case KEY_J: printf("j"); break;
      case KEY_K: printf("k"); break;
      case KEY_L: printf("l"); break;
      case KEY_M: printf("m"); break;
      case KEY_N: printf("n"); break;
      case KEY_O: printf("o"); break;
      case KEY_P: printf("p"); break;
      case KEY_Q: printf("q"); break;
      case KEY_R: printf("r"); break;
      case KEY_S: printf("s"); break;
      case KEY_T: printf("t"); break;
      case KEY_U: printf("u"); break;
      case KEY_V: printf("v"); break;
      case KEY_W: printf("w"); break;
      case KEY_X: printf("x"); break;
      case KEY_Y: printf("y"); break;
      case KEY_Z: printf("z"); break;
      
      default:
        if (inputevent.code == KEY_RESERVED || inputevent.code == KEY_ESC) {
          DoNotPrintUnkown = 1;    
        }

        if (DoNotPrintUnkown != 1) {
          printf("Unknown key pressed: %d\n", inputevent.code);  // not a letter
        }
    }

    DoNotPrintUnkown = 0;    
    fflush(stdout);
  }
  
}
