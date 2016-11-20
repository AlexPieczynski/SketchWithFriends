// addresses of each arduino
#define MASTER 0
#define SLAVE1 1
#define SLAVE2 2

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

typedef struct {
  int x;
  int y;
} Point;

typedef struct node_struct {
  Point point;
	struct node_struct* next;
} Node;

typedef struct list_struct {
	int length;
	Node* head;
} List;

enum Direction
{
  north, neast, east, seast, south, swest, west, nwest, none
};
