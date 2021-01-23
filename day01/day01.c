#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct Position
{
  int x;
  int y;
};

enum Direction
{
  NORTH = 0,
  EAST,
  SOUTH,
  WEST,
  DIRECTION_COUNT
};

const char* direction_to_string(enum Direction direction)
{
  switch(direction) {
  case NORTH: return "North";
  case EAST: return "East";
  case SOUTH: return "South";
  case WEST: return "West";
  default: return NULL;
  }
}

struct Character
{
  struct Position position;
  enum Direction direction;
};

struct Character* character_alloc(void)
{
  struct Character* character = malloc(sizeof(struct Character));
  character->position = (struct Position){0, 0};
  character->direction = NORTH;
  return character;
}

void character_free(struct Character* character)
{
  free(character);
}

enum RotationDirection
{
  LEFT,
  RIGHT
};

enum RotationDirection rotation_direction_from_char(char c)
{
  switch(c)
  {
  case 'R': return RIGHT;
  case 'L': return LEFT;
  default: abort();
  }
}

void character_rotate(struct Character* character, enum RotationDirection rotation_direction)
{
  int relative_direction = rotation_direction == RIGHT ? 1 : - 1;
  character->direction = (character->direction + relative_direction) % DIRECTION_COUNT;
}

void character_step_forward(struct Character* character, int step_count)
{
  switch(character->direction)
  {
  case NORTH:
    character->position.y += step_count;
    break;
  case EAST:
    character->position.x += step_count;
    break;
  case SOUTH:
    character->position.y -= step_count;
    break;
  case WEST:
    character->position.x -= step_count;
    break;
  default:
    break;
  }
}

void character_print(struct Character* character)
{
  printf("Position: (%d, %d)\n", character->position.x, character->position.y);
  printf("Orientation: %s\n", direction_to_string(character->direction));
}

int manhattan_distance(struct Position* a, struct Position* b);

int main(int argc, char** argv)
{
  struct Character* character = character_alloc();

  FILE* input_fp = fopen("input", "r");
  char rotation_direction_char;
  int steps;
  while (fscanf(input_fp, "%c%d, ", &rotation_direction_char, &steps) > 0)
  {
    if (feof(input_fp))
    {
      break;
    }

    character_rotate(character, rotation_direction_from_char(rotation_direction_char));
    character_step_forward(character, steps);
  }
  
  fclose(input_fp);

  character_print(character);
  printf("Manhattan distance: %d\n", manhattan_distance(&(character->position), &(struct Position){0, 0}));
  character_free(character);
  return 0;
}


int manhattan_distance(struct Position* a, struct Position* b)
{
  return abs(b->x - a->x) + abs(b->y - a->y);
}

