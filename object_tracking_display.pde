import processing.serial.*;

Serial myPort;

int angle = 0;
int distance = 0;

void setup() {

  size(1000, 700);

  println(Serial.list());

  // Change COM5 if needed
  myPort = new Serial(this, "COM5", 9600);

  myPort.bufferUntil('\n');
}

void draw() {

  background(0);

  translate(width/2, height-50);

  // Radar circles
  stroke(0,255,0);
  noFill();

  arc(0,0,800,800,PI,TWO_PI);
  arc(0,0,600,600,PI,TWO_PI);
  arc(0,0,400,400,PI,TWO_PI);
  arc(0,0,200,200,PI,TWO_PI);

  // Radar sweep line
  strokeWeight(3);

  line(
    0,
    0,
    400*cos(radians(angle)),
    -400*sin(radians(angle))
  );

  // Target point
  if(distance > 5 && distance < 100){

    stroke(255,0,0);
    strokeWeight(10);

    float r = distance * 4;

    point(
      r*cos(radians(angle)),
      -r*sin(radians(angle))
    );
  }
  // Text
  fill(0,255,0);
  textSize(25);

  text("Angle : " + angle, -450, -600);
  text("Distance : " + distance + " cm", -450, -560);

  if(distance > 5 && distance <= 20){
    fill(255,0,0);
    textSize(30);
    text("TARGET DETECTED", -450, -500);
  }
}
void serialEvent(Serial myPort) {

  String data = myPort.readStringUntil('\n');
  if(data != null){

    data = trim(data);

    println(data);

    String[] values = split(data, ',');

    if(values.length == 2){

      angle = int(values[0]);
      distance = int(values[1]);
    }
  }
} 
