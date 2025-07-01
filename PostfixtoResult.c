#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NUM 100 

typedef struct Node { 
    char data[NUM];
    struct Node* next;
    //เป็นการสร้าง linklist : ชื่อ Node ที่มี data[เก็บข้อมูลแบบ char] และ next[เก็บ address]
} Node;

Node* top = NULL; //กำหนดตัวแปร pointer top ให้ชี้ไปยังโหนดบนสุดของ 
                  //stack โดยกำหนดให้เป็น NULL เพื่อระบุว่า stack ว่าง

void push(char x[]) { 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = top;
    top = newNode;
    strcpy(newNode->data, x); 
    // strcpy(char1,char2) : การคัดลอกข้อความ จาก char2 -> char1
    // char1 : ตัวแปรข้อมูลที่เราต้องการให้เก็บ
    // char2 : ข้อความที่เราต้องการคัดลอก
    // เป็นการสร้าง node พร้อมระบุ address และ data ให้มีค่าเ่ากับ char ที่โยนเข้ามา
}

char* pop() { 
    char* popped = (char*)malloc(NUM * sizeof(char));
    Node* temp;
    if (top == NULL) {
        return NULL;
    } else {
        temp = top;
        top = top->next;
        strcpy(popped, temp->data);
        // strcpy(char1,char2) : การคัดลอกข้อความ จาก char2 -> char1
        // char1 : ตัวแปรข้อมูลที่เราต้องการให้เก็บ
        // char2 : ข้อความที่เราต้องการคัดลอก
        free(temp);
        // free(pointer) : เป็นการยกเลิกการจองพื้นที่ของ pointer เพื่อลดการใช้พื้นที่ของโปรแกรมที่ไม่ได้เรียกใช้
        return popped;
        // pop() เป็นการเรียก data ตัวบนสุดของ stack พร้อมกับทำลาย node ตัวนั้นและขยับ next
    }
}

char* Result() { 
    char* data_of_top = (char*)malloc(NUM * sizeof(char));
    if (top == NULL) {
        return NULL;
    } else {
        strcpy(data_of_top, top->data);
        // strcpy(char1,char2) : การคัดลอกข้อความ จาก char2 -> char1
        // char1 : ตัวแปรข้อมูลที่เราต้องการให้เก็บ
        // char2 : ข้อความที่เราต้องการคัดลอก
        return data_of_top;
        // Result() เป็นการ return สมการหลังดำเนินการเสร็จสิ้นแล้ว
    }
}

void print_stack_of_char() { 
    Node* temp = top;
    char dataStack[NUM][NUM];
    int index = 0;
    while (temp != NULL) {
        strcpy(dataStack[index], temp->data);
        temp = temp->next;
        index++;
        // while นี้เป็นการคัดลอกข้อมูล ที่เหลืออยู่ใน stack มาเก็บไว้ใน dataStack[index] พร้อมเพิ่มลำดับ index
    }
    for (int i = index - 1; i >= 0; i--) {
        printf("%s", dataStack[i]);
        // for นี้เป็นการพิมพ์ข้อมูล ที่คัดลอกมาไว้ใน datastack
        // เริ่มจาก index ท้ายสุด มาถึง index ที่เท่ากับ 0
    }
    printf("\n");
}

void print_stack_of_int() {
    Node* temp = top;
    char dataStack[NUM][NUM];
    int index = 0;
    while (temp != NULL) {
        strcpy(dataStack[index], temp->data);
        // strcpy(char1,char2) : การคัดลอกข้อความ จาก char2 -> char1
        // char1 : ตัวแปรข้อมูลที่เราต้องการให้เก็บ
        // char2 : ข้อความที่เราต้องการคัดลอก
        temp = temp->next;
        index++;
    }
    // while นี้เป็นการคัดลอกข้อมูลใน current มาใส่ใน dataStack 
    // ในลำดับที่ 0 จนถึง ลำดับที่ไม่มีอยู่จริง : [ลำดับสุดท้าย + 1]
    for (int i = index - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%s", dataStack[i]);
        } else {
            printf("%s, ", dataStack[i]);
        }
        // กำหนดค่า i = index - 1 : เพราะว่า while ก่อนหน้านี้หา index เกินไป 1
        // for นี้เป็นการพิมพ์ข้อมูลของ dataStack โดยเริ่มจาก index สุดท้าย จนถึง index แรกสุด
    }
    printf("\n");
}

int isOperator(char ch) { //ฟังก์ชัน isOperator ใช้สำหรับตรวจสอบตัวดำเนินการทางคณิตศาสตร์
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
    // ในการทำงาน ถ้ามี + - * / หรือ ^ จะ return  
    // ค่า 1 : ในภาษา c : 1 เป็นได้ทั้งตัวเลข และ boolean ที่เป็น true
    // ค่า 0 : ในภาษา c : 0 เป็นได้ทั้งตัวเลข และ boolean ที่เป็น true
}


void details(char ch[]) { //ฟังก์ชัน displayTablePostToIn ใช้เพื่อแสดงขั้นตอนการหาผลลัพธ์ของ postfix
    printf("========================================================\n");
    printf("%-1s%-8s%-13s%-15s\n", "", "Step", "Symbol", "Stack");
    printf("========================================================\n");
    char temp[2];
    int index = 0, result_of_int;
    while (ch[index] != '\0') { 
        // while นี้จะทำงานจนกว่า array ch มีค่าเป็น \0 : หรือก็คือ ทำจนครบทุกตัว
        // ใน details จะมีการทำงาน 2 แบบ ได้แก่ แบบตัวอักษร กับ ตัวเลข โดยใช้เงื่อนไข if else ในการตรวจสอบ
        // แบบตัวอักษร จะเป็นการติดค่าตัวแปรไว้
        // แบบตัวเลข จะเป็นการคำนวณให้อัตโนมัติ
        char example[NUM] = {'\0'}, variable_1[NUM] = {'\0'}, variable_2[NUM] = {'\0'};
        temp[0] = ch[index];
        temp[1] = '\0';
        if (isalpha(ch[0])) { 
            if (isalpha(temp[0])) { 
                push(temp);
            } else if (isOperator(temp[0])) { 
                strcpy(variable_2, pop());
                strcpy(variable_1, pop());
                sprintf(example, "(%s%s%s)", variable_1, temp, variable_2);
                push(example);
                // sprintf(str,รูปแบบที่ต้องการเก็บ,int) 
                // ใน else if นี้ได้นำมา ใช้ต่อ สมการ โดยเริ่มจาก
                // นำวงเล็บเปิดมาต่อก่อน ตามด้วย อักษรตัวที่ 1 เครื่องหาย อักษรตัวที่ 2 และ วงเล็บปิด
                // จากนั้น สร้าง node ของ example พร้อมบันทึกค่าลง data  
            } else { 
                printf("Invalid input type of postfix!\n");
                exit(0);
                //else ตัวนี้หมายถึง ในการทำงาน ถ้าเกิด ใส่เป็น ตัวอักษร ผสม ตัวเลข โปรแกรมจะ error
                //exit(0) เป็นการจบ process การทำงานของโปรแกรมทันที เพื่อป้องกันการทำงานผิดพลาด
            }
            printf("%-2s%-9d%-11c", "", index + 1, ch[index]);
            print_stack_of_char(); 
            index++;//เพิ่มลำดับให้ index = 1 
        } else if (isdigit(ch[0])) { 
            if (isdigit(temp[0])) { 
                push(temp);
            } else if (isOperator(temp[0])) { 
                strcpy(variable_2, pop());// คัดลอกค่าของ ตัวเลข ที่ 2 ให้ variable_2
                strcpy(variable_1, pop());// คัดลอกค่าของ ตัวเลข ที่ 1 ให้ variable_1
                if(temp[0]=='+'){
                    result_of_int = atoi(variable_1) + atoi(variable_2);
                }else if(temp[0]=='-'){
                    result_of_int = atoi(variable_1) - atoi(variable_2);
                }else if(temp[0]=='*'){
                    result_of_int = atoi(variable_1) * atoi(variable_2);
                }else if(temp[0]=='/'){
                    result_of_int = atoi(variable_1) / atoi(variable_2);
                }else{
                    result_of_int = pow(atoi(variable_1), atoi(variable_2));
                }
                sprintf(example, "%d", result_of_int);
                // sprintf(str,รูปแบบที่ต้องการเก็บ,int) 
                // str จะเก็บข้อมูลเป็น String ในรูปแบบที่เรากำหนด เช่นตัวอย่างข้างบน example เก็บข้อมูลเป็นรูปแบบ %d ที่ %d มีค่า = result_of_int
                push(example);// สร้าง node พร้อมบันทึก data 
            } else if (temp[0] == ' ') {
                continue;
            } else {
                printf("Invalid input type of postfix!\n");
                exit(0);
                //else ตัวนี้หมายถึง ในการทำงาน ถ้าเกิด ใส่เป็น ตัวอักษร ผสม ตัวเลข โปรแกรมจะ error
                //exit(0) เป็นการจบ process การทำงานของโปรแกรมทันที เพื่อป้องกันการทำงานผิดพลาด
            }
            printf("%-2s%-9d%-11c", "", index + 1, ch[index]);
            print_stack_of_int(); //แสดงข้อมูลใน stack
            index++; //เพิ่มลำดับให้ index = 1 
        }
    }
    printf("========================================================\n");
    char* R = Result();
    if (R != NULL) { 
        printf(" Result after convert : %s\n", R);
    } else {
        printf(" Result after convert : \n");
    }
    printf("========================================================\n");
}

int main() {
    printf("       [ENG23 2031 Data Structures and Algorithm]\n\n");
    printf("           Welcome to our project [Group 13]\n\n");
    printf("  This project can help you convert infix expressions to postfix ");
    printf("\nAn postfix expression (also called Reverse Polish Notation) \nis a single letter or an operator,preceded by two postfix strings.\nEvery postfix string longer than a single variable contains first\nand second operands followed by an operator.e.g. A,A B +,A B + C D –.");
    printf("\n\n===================== Developers =======================");
    printf("\n\n  B6500900 : Mr.Thanawit Yangngam     No.01(65)\n\n  B6512767 : Mr.Apichit Lakorn        No.39\n\n  B6513405 : Miss.Piyathida Nenchoo   No.42\n\n  B6525972 : Miss.Nichakorn Chanyutha No.64");
    printf("\n\n====================== Present =========================");
    printf("\n\n              Dr. Supaporn Bunrit");
    printf("\n\n========================================================");
    printf("\n\n                  [ Let's begin ... ]");
    printf("\n\n========= PROGRAM POSTFIX TO RESULT CONVERTER ==========\n\n");
    printf("Please Enter your Postfix : ");
    char postfix[NUM];
    fgets(postfix, sizeof(postfix), stdin); //รับข้อมูลจากแป้นพิมพ์
    // fgets ในการใช้งาน (char,int,file) 
    // char คือ ตัวแปรที่เอาไว้เก็บข้อมูล : int คือ ขนาดในการเก็บข้อมูล : file คือ ไฟล์ที่ใช้ในการอ่าน หรือ stdin
    // ในการอ่านข้อมูลของ fgets คือจะอ่านมูลที่ได้รับจนกว่าจะเจอ "\n" : [newline] นั้นเอง
    postfix[strcspn(postfix, "\n")] = '\0'; //หาตำแหน่งของ "\n" ในอาร์เรย์ และเปลี่ยนค่าเป็น '\0'
    // strcspn(char1,char2) : ในการคือค่าจะคืนเป็น index ตัวแรกที่เจอ
    // char1 : คือตัวที่เราต้องการให้คนหา
    // char2 : คือคำที่เราต้องการค้นหา
	details(postfix); // โยนข้อมูล postfix เข้าไปใน details เพื่อนทำการ process ตัว postfix to result
	printf("\n                   [ Thank you... ]\n");
    return 0;
}