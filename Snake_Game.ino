/* Initialise LED matrix */
int mat[] = {0, 0, 0, 0, 0, 0, 0, 0};
//int digit_0_l[] = {0, 0, 0b00001110, 0b00001010, 0b00001010,0b00001010, 0b00001110, 0};
//int digit_1_l[] = {0, 0, 0b00001000, 0b00001100, 0b00001000,0b00001000, 0b00011100, 0};
//int digit_2_l[] = {0, 0, 0b00011100, 0b0010000, 0b00011100,0b0000100, 0b00011100, 0}; 
//int digit_3_l[] = {0, 0, 0b00001110, 0b0001000, 0b00001110,0b0001000, 0b00001110, 0}; 
//int digit_4_l[] = {0, 0, 0b00001010, 0b00001010, 0b00001110,0b00001000, 0b00001000, 0}; 
//int digit_5_1[] = {0, 0, 0b00001110, 0b00000010, 0b00001110,0b00001000, 0b00001110, 0}; 
//int digit_6_l[] = {0, 0, 0b00001110, 0b00000010, 0b00001110,0b00001010, 0b00001110, 0};
//
//
//
//
//int digit_0_r[] = {0, 0, 0b11100000, 0b10100000, 0b10100000,0b10100000, 0b11100000, 0};
//int digit_1_r[] = {0, 0, 0b00001000, 0b00001100, 0b00001000,0b00001000, 0b00011100, 0};
//int digit_2_r[] = {0, 0, 0b11100000, 0b10000000, 0b11100000,0b0100000, 0b11100000, 0}; 
//int digit_3_r[] = {0, 0, 0b11100000, 0b10000000, 0b11100000,0b10000000, 0b11100000, 0}; 
//int digit_4_r[] = {0, 0, 0b10100000, 0b10100000, 0b11100000,0b10000000, 0b10000000, 0}; 
//int digit_5_r[] = {0, 0, 0b11100000, 0b00100000, 0b11100000,0b10000000, 0b11100000, 0}; 
//int digit_6_r[] = {0, 0, 0b11100000, 0b00100000, 0b11100000,0b10100000, 0b11100000, 0};
//int digit_7_r[] = {0, 0, 0b11100000, 0b10000000, 0b10000000,0b10000000, 0b10000000, 0};
//int digit_8_r[] = {0, 0, 0b11100000, 0b10100000,0b11100000,0b10100000, 0b11100000, 0};
//int digit_9_r[] = {0, 0, 0b11100000, 0b10100000, 0b11100000,0b10000000, 0b10000000, 0};
int tens[7][8] = {{0, 0, 0b00001110, 0b00001010, 0b00001010, 0b00001010, 0b00001110, 0},
    {0, 0, 0b00000100, 0b00000110, 0b00000100,0b00000100, 0b0001110, 0},
    {0, 0, 0b00001110, 0b0001000, 0b00001110, 0b0000010, 0b00001110, 0},
    {0, 0, 0b00001110, 0b0001000, 0b00001110, 0b0001000, 0b00001110, 0},
    {0, 0, 0b00001010, 0b00001010, 0b00001110, 0b00001000, 0b00001000, 0},
    {0, 0, 0b00001110, 0b00000010, 0b00001110, 0b00001000, 0b00001110, 0},
    {0, 0, 0b00001110, 0b00000010, 0b00001110, 0b00001010, 0b00001110, 0}
  };
  int ones[10][8] = {{0, 0, 0b11100000, 0b10100000, 0b10100000, 0b10100000, 0b11100000, 0},
    {0, 0, 0b01000000, 0b01100000, 0b01000000, 0b01000000, 0b11100000, 0},
    {0, 0, 0b11100000, 0b10000000, 0b11100000, 0b0100000, 0b11100000, 0},
    {0, 0, 0b11100000, 0b10000000, 0b11100000, 0b10000000, 0b11100000, 0},
    {0, 0, 0b10100000, 0b10100000, 0b11100000, 0b10000000, 0b10000000, 0},
    {0, 0, 0b11100000, 0b00100000, 0b11100000, 0b10000000, 0b11100000, 0},
    {0, 0, 0b11100000, 0b00100000, 0b11100000, 0b10100000, 0b11100000, 0},
    {0, 0, 0b11100000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0},
    {0, 0, 0b11100000, 0b10100000, 0b11100000, 0b10100000, 0b11100000, 0},
    {0, 0, 0b11100000, 0b10100000, 0b11100000, 0b10000000, 0b11100000, 0},
  };
/* Orb coordinates */
int orbx;
int orby;

/* Direction of movement of snake */
int dir = 1;                                                  // 0,1,2,3 correspond to up, right, down, left respectively

/* Boolean for game over */
bool gameOver = false;

/* Snake variables */
int snakeLength;
int snake[64][2];

int main() {
    Serial.begin(9600);

  /* Set up the timer */
  TCCR1B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);         // set up the pre-scalar and the mode of the timer
  OCR1A = 7000;                                               // value of ticks for 0.5 seconds
  TIMSK1 |= (1 << OCIE1A);                                    // enable the interrupt
  sei();

  /* Set up buttons for input */
  PORTB |= (1 << PB0);                                        // activate Pull Up for DOWN
  PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);              // activate Pull Ups for UP, LEFT, RIGHT
  PCICR |= (1 << PCIE0) | (1 << PCIE2);                       // set pin change interrupt control for PCMSK0 and PCMSK2 register
  PCMSK2 |= (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23); // set input bits for PORTD
  PCMSK0 |= (1 << PCINT0);                                    // set input bits for PORTB

  /* Set up SPI */
  DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);            // configure SCK, MOSI, SS as output
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);              // configure the SPI communication register
  PORTB |= (1 << PB2);                                        //Set LATCH
  sei();

  /* Generating random snake and orb */
  generateSnake();
  generateOrb();

  while (true) {
    
    if (gameOver) {
//      resetMatrix(255);
      while (true) {
        displayDigit();
//        displayMatrix();
          
        if (!(gameOver)) break;
        _delay_ms(1);
      }
      generateSnake();
      generateOrb();
      plotSnake();
      gameOver = true;
      while (gameOver) {
        displayMatrix();
        _delay_ms(1);
      }
    }
    else {
      displayMatrix();
    }
  }
  return 0;
}

ISR(PCINT0_vect) {
  gameOver = false;
  if ((PINB & (1 << PINB0)) == 0) // DOWN button
  {
    if (dir != 0) dir = 2;
  }
}
ISR(PCINT2_vect) {
  gameOver = false;
  if ((PIND & (1 << PIND6)) == 0) // LEFT button
  {
    if (dir != 1) dir = 3;
  }
  if ((PIND & (1 << PIND7)) == 0) // RIGHT button
  {
    if (dir != 3) dir = 1;
  }
  if ((PIND & (1 << PIND5)) == 0) // UP button
  {
    if (dir != 2) dir = 0;
  }
}

ISR(TIMER1_COMPA_vect) {

  gameOver = collision();
  if (gameOver) return;

  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
  }
  switch (dir) {
    case 0:
      snake[0][1]--;
      break;
    case 1:
      snake[0][0]++;
      break;
    case 2:
      snake[0][1]++;
      break;
    case 3:
      snake[0][0]--;
      break;
  }
  if (orbx == snake[0][0] && orby == snake[0][1]) {
    generateOrb();
    snakeLength++;
    OCR1A -= OCR1A * 0.1;
  }
  resetMatrix(0);
  plotSnake();
}

void resetMatrix(int row) {
  for (int i = 0; i < 8; i++) {
    mat[i] = row;
  }
}

void plotSnake() {
  mat[orby] = (1 << orbx);
  for (int i = 0; i < snakeLength; i++) {
    mat[snake[i][1]] |= (1 << snake[i][0]);
  }
}

void displayMatrix() {
  for (int i = 0; i < 8; i++) {
    PORTB &= ~(1 << PB2);
    SPDR = (1 << i);
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    SPDR = mat[i];
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    PORTB |= (1 << PB2);
  }
}

int randomizer(int low, int high) {
  randomSeed(analogRead(0));
  return random(low, high);
}

void generateOrb() {
  bool intersect = true;
  while (true) {
    if (intersect) {
      orbx = randomizer(0,8);
      orby = randomizer(0,8);
      intersect = false;
    }
    else break;
    for (int i = 0; i < snakeLength; i++) {
      if (orbx == snake[i][0] && orby == snake[i][1]) {
        intersect = true;
        break;
      }
    }
  }
}

void generateSnake() {
  OCR1A = 7000;
  snakeLength = 3;
  snake[0][0] = randomizer(2,5);
  snake[0][1] = randomizer(2,5);
  snake[1][0] = snake[0][0] - 1;
  snake[1][1] = snake[0][1];
  snake[2][0] = snake[0][0] - 2;
  snake[2][1] = snake[0][1];
  dir = 1;
}

bool collision() {
  if (snake[0][0] < 0 || snake[0][0] > 7 || snake[0][1] < 0 || snake[0][1] > 7) return true;
  for (int i = 1; i < snakeLength; i++) {
    if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) return true;
  }
  return false;
}

void displayDigit() {
  int left = (snakeLength-3)/10;
  int right = (snakeLength-3)%10;
//  Serial.print(left);
//  Serial.print(" ");
//  Serial.println(right);
  for (int i = 0; i < 8; i++) {
    PORTB &= ~(1 << PB2);
    SPDR = (1 << i);
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    SPDR = ones[right][i];
    
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    PORTB |= (1 << PB2);
  }
    for (int i = 0; i < 8; i++) {
    PORTB &= ~(1 << PB2);
    SPDR = (1 << i);
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    SPDR = tens[left][i];
    
    while (!(SPSR & (1 << SPIF))); // code to wait for SPI communication to finish
    PORTB |= (1 << PB2);
  }
}
