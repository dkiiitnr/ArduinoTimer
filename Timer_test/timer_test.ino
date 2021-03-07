bool set_timer = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(set_timer)
  { 
  inhale_timer_init(2.0);
  }
}


void inhale_timer_init(float time_in_seconds)
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  double value = (double)(65535 - (15625 * time_in_seconds));
  TCNT1 = value;                        // preload timer
  set_timer = false;
  TCCR1B |= (1 << CS10) | (1 << CS12);  // 1024 prescaler
  TIMSK1 |= (1 << TOIE1);               // enable timer overflow interrupt ISR
  Serial.println("Inhale_Timer_Init");
  interrupts();

}

ISR(TIMER1_OVF_vect)                    // interrupt service routine for Inhale timer overflow
{
  Serial.println("Inside Inhale ISR");
  set_timer = true;
}
