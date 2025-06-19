#define DATADDR DDRD
#define DATAPORT PORTD
#define DATAPIN PIND
#define WRITEDDR DDRB
#define WRITEPORT PORTB
#define WRITEPIN 0

void RAMInit()
{
  WRITEDDR=(1<<WRITEPIN);
}
void RAMWrite(uint8_t dataout)
{
  DATADDR=255;
  DATAPORT=dataout;
  WRITEPORT=(1<<WRITEPIN);
  _delay_us(5);
  WRITEPORT=0;
  DATAPORT=0;
}
char RAMRead()
{
  uint8_t datain;
  DATADDR=0;
  _delay_us(5);
  datain=DATAPIN;
  return datain;
}