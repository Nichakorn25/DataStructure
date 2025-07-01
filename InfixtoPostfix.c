#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    //เป็นการกำหนด linklist ที่มี data[เก็บข้อมูลแบบ chat] และ next[เก็บaddress]
    char data;
    struct Node* next;
} Node;

Node* top = NULL;

void push(char x) {
    // push เป็นการสร้าง node ใหม่ขึ้นมา เพื่อ บันทึกค่าของ data และ ขยับ next ไปที่ node ใหม่ 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = top;
    top = newNode;
    newNode->data = x;
}

char pop() {
    // pop เป็นการโยนค่าของ data พร้อมลบnode และ ขยับ next ไปทางซ้าย
    char popped;
    Node* temp;
    if (top == NULL) {
        return '\0';
    } else {
        temp = top;
        top = top->next;
        popped = temp->data;
        free(temp);
        return popped;
    }
}

char stack_on_top() {
    //ใช้เพื่อเช็คข้อมูลตัวบนสุด
    if (top == NULL) {
        return '\0';
    } else {
        return top->data;
    }
}

int check_level_of_priority(char temp) {
    //เช็ค level ของ operator ที่โยนเข้ามา
    int priority;
    if (temp == '(') {
        priority = 0;
    } else if (temp == '^') {
        priority = 3;
    } else if (temp == '*' || temp == '/') {
        priority = 2;
    } else {
        priority = 1;
    }
    return priority;
}

void detail(char ch[], int size) {
    printf("========================================================\n");
    printf("%-1s%-8s%-13s%-15s%-20s\n", "", "Step", "Symbol", "Stack", "Output");
    printf("========================================================\n");
    char stack[size], output[size];
    //ทำการสร้าง array ของ stack และ ของ output ขึ้นมา่ในขนาดของ size 
    for (int i = 0; i <= size; i++) {
        stack[i] = '\0';
        output[i] = '\0';
        //For นี้เป็นการเซ็ตค่าให้ array ในแต่ละ index เป็นช่องว่าง เพื่อป้องกันไม่ให้ค่าที่แสดงออก ไม่ตรงตามที่ต้องการ
    }
    int i, num_stack = 0, num_output = 0;
    for (i = 0; i < size; i++) {
        if (ch[i] == '(') {
            push(ch[i]);
            stack[num_stack++] = ch[i];
            printf("%-2s%-8d%-13c%-15s%-20s\n", "", i + 1, ch[i], stack, output);
            //ทำการเซ็ตค่าให้ array stack และเพิ่มค่าของ index stack และปริ้นข้อมูลออกมา
        } else if (isalnum(ch[i])) {
            output[num_output++] = ch[i];
            printf("%-2s%-8d%-13c%-15s%-20s\n", "", i + 1, ch[i], stack, output);
            //ในส่วนของ isalnum() เป็นฟังก์ชั่น ในการเช็คว่าเป็น ตัวอักษร หรือ ตัวเลข หรือป่าว ถ้าใช่จะคืนค่าเป็น true ถ้าไม่ใช่จะเป็น false
            //และทำการเซ็ตค่าให้ array output พร้อมกับเพิ่มค่า index output
        } else if (ch[i] == ')') {
            while (stack_on_top() != '(') {
                output[num_output++] = pop();
                stack[num_stack--] = '\0';
            }
            pop();
            stack[num_stack--] = '\0';
            stack[num_stack] = '\0';
            printf("%-2s%-8d%-13c%-15s%-20s\n", "", i + 1, ch[i], stack, output);
            //ถ้าเจอ ')' จะทำการใช้เรียนกใช้ stacktop เพื่อดึงข้อมูลออกมาเช็ค 
            //และทำการเซ็ตค่าให้ array output พร้อมกับเพิ่มค่า index output
            //พร้อมเซ็ตค่า ของ array stack ให้เป็นช่องว่าง
            //เมื่อจบ while จะทำการ pop '(' และ เซ็ตค่าของที่เหลืออยู่ใน array stack ให้เป็น ช่องว่าง 
        } else {
            //else ส่วนนี้เป็น ของกรณี isalnum() เมื่อไม่ใช่ ตัวอักษร หรือ ตัวเลข
            if (stack_on_top() == '\0' || stack_on_top() == '(') {
                push(ch[i]);
                stack[num_stack++] = ch[i];
                printf("%-2s%-8d%-13c%-15s%-20s\n", "", i + 1, ch[i], stack, output);
                //ในส่วนนี้จะเรียกใช้ stacktop เพื่อดูข้อมูลของ data ตัวบนสุด ว่าเป็น ช่องว่างหรือวง '('
                //ถ้าเป็นจริง จะทำการ push ข้อมูลพร้อมสร้าง node ใหม่ให้ top 
                //และทำการเซ็ตค่าให้ array stack พร้อมกับเพิ่มค่า index stack
            } else {
                //ถ้าเกิดว่า top ยังไม่ใช่ช่องว่าง หรือวงเล็บ
                //จะทำการเรียกใช้ checkPriority เพื่อดู level ของ เครื่องหมาย
                // ^   level : 3
                // * / level : 2
                // ตัวอื่นๆ level : 1
                // (   level : 0
                if (check_level_of_priority(ch[i]) <= check_level_of_priority(stack_on_top())) {
                    //ถ้าเกิดข้อมูลของ array ch มี level น้อยกว่า ข้อมูลตัวบนสุด
                    while ((check_level_of_priority(ch[i]) <= check_level_of_priority(stack_on_top())) && (stack_on_top() != '\0')) {
                        //ทำการตรวจสอบ level ของ ch มีค่า < ข้อมูลตัวบนสุด และ ตัวบนสุดต้องไม่เป็นช่องว่าง
                        //จะทำจนกว่าจะเจอ ตัวที่เลเวล มากกว่า
                        //พร้อมกับเซ็ตค่า array stack ให้เป็นช่องว่าง พร้อมกับลด index stack
                        //และทำการเซ็ตค่าให้ array output พร้อมกับเพิ่มค่า index output ข้อมูลที่เซ็ตคือ ตัวบนสุด(pop)
                        stack[num_stack--] = '\0';
                        output[num_output++] = pop();
                    }
                }
                //ถ้าเกิดว่า level ของ ch มากกว่า ข้อมูลตัวบนสุด จะทำการ push
                //และทำการเซ็ตค่าให้ array stack พร้อมกับเพิ่มค่า index stack
                push(ch[i]);
                stack[num_stack++] = ch[i];
                printf("%-2s%-8d%-13c%-15s%-20s\n", "", i + 1, ch[i], stack, output);
            }
        }
    }
    int check_output_of_data = 0;
    while (stack_on_top() != '\0') {
        output[num_output++] = pop();
        check_output_of_data++;
        //ในส่วนของ while เพื่อเช็คว่ามีค่าเหลืออยู่ใน data[ข้อมูลตัวบนสุด หรือ ขวาสุด] รึป่าว
        //ถ้ามีจะทำการ เซ็ตค่าให้ array output พร้อมกับเพิ่มค่า index output ข้อมูลที่เซ็ตคือ ตัวบนสุด(pop) จน data ไม่เหลือข้อมูล
        //พร้อมเพิ่มค่า check_output_of_data
    }
    if (check_output_of_data > 0) {
        printf("%-2s%-8d%-13s%-15s%-20s\n", "", i + 1, "", "", output);
        //ตรงนี้จะเป็นการโชว์บรรทัดการเคลีย data ที่เหลืออยู่ทั้งหมด
    }
    printf("========================================================\n");
    printf("Postfix: %s\n", output);
    //ตรงส่วนนี้เป็นการโชว์คำตอบที่เสร็จหมดแล้ว
    printf("========================================================\n");
}

int main() {
    printf("       [ENG23 2031 Data Structures and Algorithm]\n\n");
    printf("           Welcome to our project [Group 13]\n\n");
    printf("  This project can help you convert infix expressions to postfix ");
    printf("\nInfix expression: The expression of the form “a operator b” (a + b)\nPostfix expression: The expression of the form “a b operator” (ab+)");
    printf("\nExample This Program : We can convert a+b to ab+");
    printf("\n\n===================== Developers =======================");
    printf("\n\n  B6500900 : Mr.Thanawit Yangngam     No.01(65)\n\n  B6512767 : Mr.Apichit Lakorn        No.39\n\n  B6513405 : Miss.Piyathida Nenchoo   No.42\n\n  B6525972 : Miss.Nichakorn Chanyutha No.64");
    printf("\n\n====================== Present =========================");
    printf("\n\n                Dr. Supaporn Bunrit");
    printf("\n\n========================================================");
    printf("\n\n                  [ Let's begin ... ]");
    printf("\n\n========= PROGRAM : INFIX TO POSTFIX CONVERTER =========\n\n");
    printf("Please Enter your Infix \n\n");
    char c;
    int size = 0;
    printf("Infix : ");
    while (scanf("%c", &c) && c != '\n') {
        if(c != ' '){
        size++;
        push(c);
        }
        //ใน While นี้จะเป็นการรับ ตัวอักษร ทีละตัว เข้าไปใน data และ ขยับ next ไปทางขวา
    }
    char ch[size];
    for (int i = size - 1; i >= 0; i--) {
        ch[i] = pop();
        //ใน For ตรงนี้จะเป็นการนำค่า data ที่ index ท้ายสุด มาใส่ array ch และทำการขยับ next ไปทาง ซ้าย
        //ในส่วนของ index จะเพิ่มจากท้าย -> 0 
    }
    detail(ch, size); //โยน arr ch เข้าไปใน detail เพิ่มเริ่มกระบวนการทำงาน
    printf("\n                   [ Thank you... ]");
    printf("\n ");
    return 0;
}