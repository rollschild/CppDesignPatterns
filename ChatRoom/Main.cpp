#include <iostream>

#include "Person.h"
#include "ChatRoom.h"

int main() {
  ChatRoom room;

  Person jovi{"Jovi"};
  Person eva{"Eva"};
  room.Join(&jovi);
  room.Join(&eva);

  jovi.Speak("Hello, everybody!");
  eva.Speak("Oh, hi Jovi! Welcome!");

  Person dudu{"dudu"};
  room.Join(&dudu);

  dudu.Speak("Ni hao!");
  jovi.PrivateMessage("dudu", "How you doing, dudu?");

  return 0;
}
