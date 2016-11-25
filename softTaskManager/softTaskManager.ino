
#define MAX_TASKS 5
struct Task_sheduler {
  void (*TASK_handler)();
  unsigned long period;
  unsigned long prevMillis;
  bool runnable;
} task[MAX_TASKS];
byte task_count = 0;

void Task_1() {
  digitalWrite(13, !digitalRead(13));
}

void Task_2() {
  Serial.print("Task count: ");
  Serial.println(task_count);
}

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  addTask(Task_1, 200);
  addTask(Task_2, 1000);
}

void loop() {
  sheduler_Handler();
}

void runTask() {
  task[0].runnable = true;
}

void stopTask() {
  task[0].runnable = false;
}

void addTask(void (*handler)(), unsigned long period) {
  if(task_count<MAX_TASKS) {
    task[task_count].TASK_handler = handler;
    task[task_count].period = period;
    task[task_count].runnable = false;
    task_count++;
  }
}

void sheduler_Handler() {
  for(byte i=0; i<task_count; i++) {
    if(millis() - task[i].prevMillis >= task[i].period)  {
      task[i].TASK_handler();
      task[i].prevMillis = millis();
    }
  }  
}

