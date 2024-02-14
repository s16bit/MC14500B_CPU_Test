byte clk_pin = 7;
byte rst_pin = 6;

byte data_pin = 5;

#define LENGTH 4

byte opcode_pins[LENGTH] = {1, 2, 3, 4};

#define NOPO B0000
#define LD B0001
#define LDC B0010
#define AND B0011
#define ANDC B0100
#define OR B0101
#define ORC B0110
#define XNOR B0111
#define STO B1000
#define STOC B1001
#define IEN B1010
#define OEN B1011
#define JMP B1100
#define RTN B1101
#define SKZ B1110
#define NOPF B1111

#define H | 16
#define L | 0

void setup() {
  
  pinMode(clk_pin, OUTPUT);
  pinMode(rst_pin, OUTPUT);

  pinMode(data_pin, OUTPUT);

  for(byte i = 0; i < LENGTH; i++) pinMode(opcode_pins[i], OUTPUT);

  digitalWrite(clk_pin, LOW);
  
  digitalWrite(rst_pin, HIGH);
  delay(100);
  digitalWrite(rst_pin, LOW);
  
}

void loop() {

  byte _size = 3;
  
  const byte program[_size] = {
    NOPF,
    IEN H,
    OEN H
  };
  
  for(byte i = 0; i < _size; i++) {
    send_instruction(program[i]);
  }
  
  while(1) {
    
    send_instruction(XNOR L);
    
  }

}

void tick(int mills) {
  
  digitalWrite(clk_pin, LOW);
  delay(mills);
  digitalWrite(clk_pin, HIGH);
  delay(mills);
  digitalWrite(clk_pin, LOW);
  
}

void send_instruction(byte instruction) {

  for(byte _bit = 0; _bit < LENGTH; _bit++) {
    digitalWrite(opcode_pins[_bit], instruction >> _bit & 1);
  }

  digitalWrite(data_pin, instruction & 16);
  
  tick(2500);
  
}
