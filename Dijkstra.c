// โปรแกรม C สำหรับ Dijkstra's single source shortest path algorithm
// โปรแกรมนี้ใช้ adjacency matrix เพื่อแสดงกราฟ

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// จำนวน vertices ในกราฟ
#define V 9
#define INF 9999
// โครงสร้างข้อมูล Stack
struct Stack {
    int capacity;  // ความจุของ Stack
    int top;        // ดัชนีของ Stack
    int *array;     // อาร์เรย์เก็บข้อมูลใน Stack
};

// ฟังก์ชันสร้าง Stack
// พารามิเตอร์ capacity: จำนวนสูงสุดของข้อมูลที่ Stack สามารถเก็บได้
struct Stack* createStack(int capacity) {
    // ใช้ malloc เพื่อจองพื้นที่ในหน่วยความจำสำหรับ struct Stack
    struct Stack* stack = malloc(sizeof(struct Stack));

    // กำหนดค่าใน struct Stack
    stack->capacity = capacity;  // กำหนดความจุของ Stack
    stack->top = -1;             // กำหนดค่า top ให้เป็น -1 เพื่อระบุว่า Stack ว่าง
    // ใช้ malloc เพื่อจองพื้นที่ในหน่วยความจำสำหรับ array ที่ใช้เก็บข้อมูลใน Stack
    stack->array = malloc(stack->capacity * sizeof(int));

    // ส่งค่ากลับเป็น pointer ไปยัง Stack ที่สร้างขึ้น
    return stack;
}


// ฟังก์ชันใส่ข้อมูลลงใน Stack
void push(struct Stack* stack, int item) {//void push(struct Stack* stack, int item): ประกาศฟังก์ชัน push ที่รับ Stack เป็นพารามิเตอร์แรกและข้อมูลที่ต้องการใส่เป็นพารามิเตอร์ที่สอง (item)
    stack->array[++stack->top] = item;//stack->array[++stack->top] = item;: เพิ่มค่าของ top ของ Stack และใส่ข้อมูลลงใน array ที่ตำแหน่ง stack->top. การใช้ ++stack->top ทำให้ค่า top เพิ่มขึ้นก่อนที่จะนำไปใช้ในการอ้างถึง array ที่ต้องการใส่ข้อมูล
}

// ฟังก์ชันดึงข้อมูลจาก Stack
int pop(struct Stack* stack) {//int pop(struct Stack* stack): ประกาศฟังก์ชัน pop ที่รับ Stack เป็นพารามิเตอร์
    return stack->array[stack->top--];//return stack->array[stack->top--];: นำข้อมูลที่อยู่ที่ด้านบนสุดของ Stack ออก โดยให้ค่าที่ตำแหน่ง stack->top และลดค่าของ top. การใช้ stack->top-- ทำให้ค่า top ลดลงก่อนที่จะนำไปใช้ในการอ้างถึง array ที่ต้องการดึงข้อมูล
}

// ฟังก์ชันตรวจสอบว่า Stack ว่างหรือไม่
int isEmpty(struct Stack* stack) {//int isEmpty(struct Stack* stack): ประกาศฟังก์ชัน isEmpty ที่รับ Stack เป็นพารามิเตอร์
    return stack->top == -1;//return stack->top == -1;: คืนค่าเป็น true ถ้าค่าของ top มีค่าเท่ากับ -1 (Stack ว่าง), มิฉะนั้นคืนค่าเป็น false
}

// ฟังก์ชันดึงข้อมูลที่อยู่บน Stack
int peek(struct Stack* stack) {//int peek(struct Stack* stack): ประกาศฟังก์ชัน peek ที่รับ Stack เป็นพารามิเตอร์
    return stack->array[stack->top];//return stack->array[stack->top];: คืนค่าข้อมูลที่อยู่ที่ด้านบนสุดของ Stack โดยใช้ค่า top ในการอ้างถึง array
}

// ฟังก์ชันหา vertex ที่มีระยะทางน้อยที่สุด
int minDistance(int dist[], bool sptSet[]) {//int minDistance(int dist[], bool sptSet[]): ประกาศฟังก์ชัน minDistance ที่รับอาร์เรย์ dist และ sptSet เป็นพารามิเตอร์
    int min = INF, min_index;//int min = INT_MAX, min_index;: ประกาศตัวแปร min และ min_index โดยกำหนดค่าเริ่มต้นของ min เป็น INT_MAX
    //#define v = 9
    for (int v = 0; v < V; v++)//for (int v = 0; v < V; v++): วนลูปเพื่อตรวจสอบทุก vertex ในกราฟ
        if (sptSet[v] == false && dist[v] <= min)//if (sptSet[v] == false && dist[v] <= min): ตรวจสอบว่า vertex v ไม่ได้รวมเข้าใน shortest path tree และระยะทางจาก source ไปยัง v น้อยกว่าหรือเท่ากับ min
            min = dist[v], min_index = v;//min = dist[v], min_index = v;: กำหนดค่า min เป็น dist[v] และ min_index เป็น v หากเงื่อนไขถูกต้อง

    return min_index;//return min_index;: คืนค่า index ของ vertex ที่มีระยะทางน้อยที่สุด
}

// ฟังก์ชันแสดงเส้นทางที่สั้นที่สุด
void printPath(struct Stack* pathStack) {
    while (!isEmpty(pathStack)) {// วนลูปจนกว่า Stack จะว่าง
        printf("%c ", 'A' + pop(pathStack));//('A' + pop(pathStack) จะนำค่าที่ได้จากการ pop ออกจาก Stack มาบวกกับ ASCII value ของ 'A' เพื่อแปลงเป็นตัวอักษรที่แทน vertex นั้น ๆ ในกราฟ) แสดง vertex ที่อยู่ด้านบนสุดของ Stack และนำข้อมูลนั้นออกจาก Stack
        if (!isEmpty(pathStack)) {
            printf("-> "); // แสดงลูกศรถัดไปถ้า Stack ยังไม่ว่าง
        }
    }//stack ถูกสร้างมาเพื่อเก็บเส้นทางที่สั้นที่สุด
}

// ฟังก์ชันแสดงผลลัพธ์การคำนวณ
// ฟังก์ชัน printSolution ใช้เพื่อแสดงผลลัพธ์ของ Dijkstra's algorithm
void printSolution(int dist[], int parent[], int src) {
    struct Stack* pathStack = createStack(V); // สร้าง Stack เพื่อเก็บเส้นทางที่สั้นที่สุด
    printf("====================================\n");
    printf("Vertex \t\t Distance \t\t Path\n");
    printf("====================================\n");
    for (int i = 0; i < V; i++) {
        printf("%c -> %c \t\t %5d \t\t\t ", 'A' + src, 'A' + i, dist[i]); // แสดงข้อมูลเกี่ยวกับระยะทางที่สั้นที่สุด
        int j = i;
        while (j != src) { // วนลูปเพื่อเก็บ vertex ลงใน Stack เพื่อสร้างเส้นทางที่สั้นที่สุด
            push(pathStack, j);
            j = parent[j];
        }
        push(pathStack, src); // เก็บ source vertex ลงใน Stack
        printPath(pathStack); // แสดงเส้นทางที่สั้นที่สุดโดยใช้ฟังก์ชัน printPath
        printf("\n"); // ขึ้นบรรทัดใหม่เพื่อความกระชับในการแสดงผล
    }
}


// ฟังก์ชัน Dijkstra's single source shortest path algorithm
// ทำการคำนวณระยะทางที่สั้นที่สุดจากต้นทางไปยังทุก vertex ในกราฟ
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // อาร์เรย์ dist ใช้เก็บระยะทางที่สั้นที่สุดจากต้นทางไปยังแต่ละ vertex ในกราฟ
    int parent[V]; // อาร์เรย์ parent ใช้เก็บข้อมูลว่า vertex ที่มีระยะทางที่สั้นที่สุดไปยัง vertex นั้น ๆ คือ vertex ใดๆ
    bool sptSet[V]; // อาร์เรย์ sptSet (shortest path tree set) ใช้เก็บข้อมูลเกี่ยวกับการเลือก vertex ที่มีระยะทางที่สั้นที่สุดแล้ว

    // กำหนดค่าเริ่มต้น
    // #define V = 9
    //#define INT_MAX = 9999
    for (int i = 0; i < V; i++) {
        dist[i] = INF; // กำหนดระยะทางเริ่มต้นให้เป็นค่า Infinity
        sptSet[i] = false; // ยังไม่ได้เลือก vertex ที่มีระยะทางที่สั้นที่สุด(unvisited)
    }
    dist[src] = 0; // ระยะทางจากต้นทางไปยังตนเองเป็น 0
    parent[src] = -1; // ไม่มี vertex ที่เป็น parent ของตนเอง

    // ค้นหา shortest path
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // เลือก vertex ที่มีระยะทางที่สั้นที่สุด(ส่ง ค่าindex ที่มี ค่าระยะทางที่สั้นที่สุดให้ u)
        sptSet[u] = true; // เลือก vertex นี้แล้ว (ทำเครื่องหมายว่าไป visited แล้วโดยใส่ boolean หากเป็น true = visted, false = unvisited)

        for (int v = 0; v < V; v++) {
            // ตรวจสอบ vertex ที่ยังไม่ได้เลือก, มีเส้นเชื่อม, ระยะทางจากต้นทางไปยัง u ไม่เท่ากับ Infinity,
            // และระยะทางจากต้นทางไปยัง u + เส้นเชื่อมไปยัง v น้อยกว่าระยะทางปัจจุบันที่รู้ไว้
            if (!sptSet[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {//!sptSet[v]: ตรวจสอบว่า vertex v ยังไม่ได้ถูกเลือกเข้าใน Shortest Path Tree (SPT) or unvisited
                //graph[u][v]: ตรวจสอบว่ามีเส้นเชื่อมระหว่าง vertex u กับ v. ถ้าเป็น true,แสดงว่ามีทางเชื่อมระหว่าง vertex u กับ v
                //dist[u] != INT_MAX: ตรวจสอบว่าระยะทางจากต้นทางไปยัง vertex u ไม่เป็น Infinity. ถ้าเป็น Infinity, หมายความว่ายังไม่มีทางเชื่อมระหว่าง source vertex v กับ vertex u
                //dist[u] + graph[u][v] < dist[v]: ตรวจสอบว่าระยะทางที่ได้จาก source vertex ไปยัง v ผ่าน u น้อยกว่าระยะทางปัจจุบันที่มีอยู่ (ใน dist[v]).
          //=================================================================
                //ถ้าทุกเงื่อนไขเป็นจริง, คำสั่งทำงาน:
    //dist[v] = dist[u] + graph[u][v];: ปรับปรุงค่าระยะทางที่สั้นที่สุดจาก source vertex ไปยัง vertex v โดยใช้เส้นทางที่ผ่าน vertex u.
    //parent[v] = u;: กำหนด vertex u เป็น parent ของ vertex v, หมายความว่าเส้นทางที่สั้นที่สุดจาก source vertex ไปยัง vertex v ได้ผ่าน vertex u.
    //ดังนั้น, คำสั่งนี้ทำให้เราปรับปรุงระยะทางที่สั้นที่สุดและติดตามเส้นทางที่สั้นที่สุดจาก source vertex ไปยังทุก vertex ที่มีเส้นเชื่อม
                dist[v] = dist[u] + graph[u][v]; // ปรับปรุงระยะทางที่สั้นที่สุด update ค่าdistance
                parent[v] = u; // กำหนด vertex u เป็น parent ของ vertex v
            }
        }
    }

    // แสดงผลลัพธ์
    printSolution(dist, parent, src);
}

// ฟังก์ชันหลัก
int main() {
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    char sourceVertex;
    char next;
    printf("        [ENG23 2031 Data Structures and Algorithm]\n\n");
    printf("            Welcome to our project [Group 13]\n\n");
    printf("   This project is Dijkstra's Algorithm finds the shortest path between a given node (which is called the (source node) and all other nodes in a graph.  ");
    printf("\n\n====================== Developers =======================");
    printf("\n\nB6500900 Thanawit Yangngam   No.1(65)\n\nB6512767 Apichit Lakorn      No.39\n\nB6513405 Piyathida Nenchoo   No.42\n\nB6525972 Nichakorn Chanyutha No.64");
    printf("\n\n====================== Present =========================");
    printf("\n\nDr. Supaporn Bunrit");
    printf("\n\n========================================================\n\n");
    printf("Enter the source vertex (A to I): ");
    scanf(" %c", &sourceVertex);
    int source = sourceVertex - 'A';

    dijkstra(graph, source);

    return 0;
}