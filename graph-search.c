#include <stdio.h> //표준입출력을 담당하는 <stdio.h> 헤더파일 선언
#include <stdlib.h> //표준 라이브러리를 담당하는 <stdlib.h> 헤더파일 선언

#define MAX_VERTICES 10 //최대 정점 수를 10으로 정의

typedef struct Node { //노드 구조체 정의
    int vertex; //정점을 나타내는 vertex 변수 선언
    struct Node* next; //다음 노드를 가리키는 next 포인터 선언
} Node;

typedef struct Graph { //그래프 구조체 정의
    Node* adjList[MAX_VERTICES]; //인접 리스트를 나타내는 adjList 배열 선언
    int visited[MAX_VERTICES]; //방문 여부를 나타내는 visited 배열 선언
} Graph;

Graph* createGraph(); //그래프를 생성하는 createGraph 함수 원형 선언
void addVertex(Graph* graph, int vertex); //정점을 추가하는 addVertex 함수 원형 선언
void addEdge(Graph* graph, int src, int dest); //간선을 추가하는 addEdge 함수 원형 선언
void printGraph(Graph* graph); //그래프를 출력하는 printGraph 함수 원형 선언
void DFS(Graph* graph, int startVertex); //깊이 우선 탐색을 하는 DFS 함수 원형 선언
void BFS(Graph* graph, int startVertex); //너비 우선 탐색을 하는 BFS 함수 원형 선언
Node* createNode(int vertex); //노드를 생성하는 createNode 함수 원형 선언
void clearVisited(Graph* graph); //방문 여부를 초기화하는 clearVisited 함수 원형 선언

int main(void) //main 함수 시작
{
    printf("[----- [배정민] [2023041088] -----]\n");

    Graph* graph = createGraph(); //그래프를 생성하고 graph 포인터에 할당
    char command; //명령어를 입력받을 command 변수 선언
    int vertex, search, destination; //정점, 탐색, 목적지를 입력받을 변수 선언

    printf("Graph Searches\n");
    printf("-------------------------------------------------\n");
    printf("Initialize Graph = z\n");
    printf("Insert Vertex = v       Insert Edge = e\n");
    printf("Depth First Search = d  Breadth First Search = b\n");
    printf("Print Graph = p         Quit = q\n");
    printf("-------------------------------------------------\n");

    while (1)
    {
        printf("Enter command: ");
        scanf(" %c", &command);
        
        switch (command)
        {
            case 'z':
                graph = createGraph();
                printf("Graph initialized.\n");
                break;
            case 'v':
                printf("Enter vertex (0-9): ");
                scanf("%d", &vertex);
                if (vertex < 0 || vertex >= MAX_VERTICES) //입력받은 vertex가 0보다 작거나 같거나 MAX_VERTICES(10)보다 크거나 같으면
                {
                    printf("Invalid vertex number.\n"); //정점 번호가 유효하지 않음을 출력
                }
                else //아니면
                {
                    addVertex(graph, vertex); //addVertex 함수 호출
                }
                break;
            case 'e':
                printf("Enter source and destination vertices (0-9): ");
                scanf("%d %d", &search, &destination);
                if (search < 0 || search >= MAX_VERTICES || destination < 0 || destination >= MAX_VERTICES) //입력받은 search나 destination이 0보다 작거나 MAX_VERTICES(10)보다 크거나 같으면
                {
                    printf("Invalid vertex numbers.\n"); //정점 번호가 유효하지 않음을 출력
                }
                else //아니면
                {
                    addEdge(graph, search, destination); //addEdge 함수 호출
                }
                break;
            case 'd':
                printf("Enter start vertex for DFS (0-9): ");
                scanf("%d", &vertex);
                if (vertex < 0 || vertex >= MAX_VERTICES) //입력받은 vertex가 0보다 작거나 MAX_VERTICES(10)보다 크거나 같으면
                {
                    printf("Invalid vertex number.\n"); //정점 번호가 유효하지 않음을 출력
                }
                else //아니면
                {
                    clearVisited(graph); //clearVisited 함수 호출해서 방문 여부 초기화
                    DFS(graph, vertex); //DFS 함수 호출
                    printf("\n");
                }
                break;
            case 'b':
                printf("Enter start vertex for BFS (0-9): ");
                scanf("%d", &vertex);
                if (vertex < 0 || vertex >= MAX_VERTICES) //입력받은 vertex가 0보다 작거나 MAX_VERTICES(10)보다 크거나 같으면
                {
                    printf("Invalid vertex number.\n"); //정점 번호가 유효하지 않음을 출력
                }
                else //아니면
                {
                    clearVisited(graph); //clearVisited 함수 호출해서 방문 여부 초기화
                    BFS(graph, vertex); //BFS 함수 호출
                    printf("\n");
                }
                break;
            case 'p':
                printGraph(graph); //printGraph 함수 호출
                break;
            case 'q':
                printf("Quitting program.\n");
                return 0;
            default:
                printf("Invalid command.\n");
        }
    }
    return 0;
}

Graph* createGraph() //그래프를 생성하는 createGraph 함수 정의
{
    Graph* graph = (Graph*) malloc(sizeof(Graph)); //그래프의 크기만큼 동적 메모리 할당
    
    for (int i = 0; i < MAX_VERTICES; i++) //i가 0부터 MAX_VERTICES(10)보다 작을 때까지 반복
    {     
        graph->visited[i] = 0; //graph의 visited[i]에 0 할당(방문여부를 0으로 설정)
        graph->adjList[i] = NULL; //graph의 adjList[i]에 NULL 할당
    }
    return graph; //graph 반환
}

Node* createNode(int vertex) //노드를 생성하는 createNode 함수 정의
{
    Node* newNode = (Node*) malloc(sizeof(Node)); //노드의 크기만큼 동적 메모리 할당
    
    newNode->vertex = vertex; //newNode의 vertex에 vertex 할당
    newNode->next = NULL; //newNode의 next에 NULL 할당
    
    return newNode; //newNode 반환
}

void addVertex(Graph* graph, int vertex) //정점을 추가하는 addVertex 함수 정의
{
    if (graph->adjList[vertex] == NULL) //만약 graph의 adjList[vertex]가 비어있으면
    {
        graph->adjList[vertex] = createNode(vertex); //createNode 함수를 호출해서 vertex를 생성하고 graph의 adjList[vertex]에 할당
        printf("Vertex %d added.\n", vertex); //vertex가 추가되었음을 출력
    }
    else //아니면
    {
        printf("Vertex %d already exists.\n", vertex); //vertex가 이미 존재함을 출력
    }
}

void addEdge(Graph* graph, int src, int dest) //간선을 추가하는 addEdge 함수 정의
{
    Node* newNode = createNode(dest); //createNode 함수를 호출해서 dest를 생성하고 newNode에 할당
    Node* temp = graph->adjList[src]; //temp에 graph의 adjList[src] 할당
    
    if (temp == NULL) //만약 temp가 비어있으면
    {
        graph->adjList[src] = newNode; //newNode를 graph의 adjList[src]에 할당
    }
    else //아니면
    {
        while (temp->next != NULL) //temp의 next가 NULL이 아닐 때까지 반복
        {
            temp = temp->next; //temp에 temp의 next 할당
        }
        
        temp->next = newNode; //temp의 next에 newNode 할당
    }
    
    printf("Edge added from %d to %d.\n", src, dest);

    newNode = createNode(src); //createNode 함수를 호출해서 src를 생성하고 newNode에 할당
    temp = graph->adjList[dest]; //temp에 graph의 adjList[dest] 할당
    
    if (temp == NULL) //만약 temp가 비어있으면
    {
        graph->adjList[dest] = newNode; //newNode를 graph의 adjList[dest]에 할당
    }
    else //아니면
    {
        while (temp->next != NULL) //temp의 next가 NULL이 아닐 때까지 반복
        {
            temp = temp->next; //temp에 temp의 next 할당
        }
        
        temp->next = newNode; //temp의 next에 newNode 할당
    }

    printf("Edge added from %d to %d.\n", dest, src);
}

void printGraph(Graph* graph) //그래프를 출력하는 printGraph 함수 정의
{
    for (int i = 0; i < MAX_VERTICES; i++) //i가 0부터 MAX_VERTICES(10)보다 작을 때까지 반복
    {
        Node* temp = graph->adjList[i]; //temp에 graph의 adjList[i] 할당
        if (temp != NULL) //만약 temp가 비어있지 않으면
        {
            printf("Vertex %d: ", i); //정점 i 출력
            
            while (temp != NULL) //temp가 NULL이 아닐 때까지 반복
            {
                printf("%d -> ", temp->vertex); //temp의 vertex 출력
                temp = temp->next; //temp에 temp의 next 할당
            }
            printf("NULL\n"); //NULL 출력(끝을 나타냄)
        }
    }
}

void DFS(Graph* graph, int vertex) //깊이 우선 탐색을 하는 DFS 함수 정의
{
    if (graph == NULL) //만약 graph가 비어있으면
    {
        printf("Graph is empty.\n"); //그래프가 비어있음을 출력
        return; //종료
    }

    Node* adjList = graph->adjList[vertex]; //adjList에 graph의 adjList[vertex] 할당
    Node* temp = adjList; //temp에 adjList 할당

    graph->visited[vertex] = 1; //graph의 visited[vertex]에 1 할당
    printf("%d ", vertex); //vertex 출력

    while (temp != NULL) //temp가 NULL이 아닐 때까지 반복
    {
        int connectedVertex = temp->vertex; //connectedVertex에 temp의 vertex 할당
        if (graph->visited[connectedVertex] == 0) //만약 graph의 visited[connectedVertex]가 0이면
        {
            DFS(graph, connectedVertex); //DFS 함수 호출
        }
        temp = temp->next; //temp에 temp의 next 할당
    }
}

void BFS(Graph* graph, int startVertex) //너비 우선 탐색을 하는 BFS 함수 정의
{
    if (graph == NULL) //만약 graph가 비어있으면
    {
        printf("Graph is empty.\n"); //그래프가 비어있음을 출력
        return; //종료
    }

    Node* queue[MAX_VERTICES]; //queue 배열 선언
    int front = 0; //front 변수 선언
    int rear = 0; //rear 변수 선언

    graph->visited[startVertex] = 1; //graph의 visited[startVertex]에 1 할당
    queue[rear++] = graph->adjList[startVertex]; //queue[rear]에 graph의 adjList[startVertex] 할당하고 rear 증가

    while (front < rear) //front가 rear보다 작을 때까지 반복
    {
        Node* current = queue[front++]; //current에 queue[front] 할당하고 front 증가
        printf("%d ", current->vertex); //current의 vertex 출력

        Node* temp = graph->adjList[current->vertex]; //temp에 graph의 adjList[current->vertex] 할당

        while (temp != NULL) //temp가 NULL이 아닐 때까지 반복
        {
            int adjVertex = temp->vertex; //adjVertex에 temp의 vertex 할당

            if (graph->visited[adjVertex] == 0) //만약 graph의 visited[adjVertex]가 0이면
            {
                graph->visited[adjVertex] = 1; //graph의 visited[adjVertex]에 1 할당
                queue[rear++] = graph->adjList[adjVertex]; //queue[rear]에 graph의 adjList[adjVertex] 할당하고 rear 증가
            }
            temp = temp->next; //temp에 temp의 next 할당
        }
    }
}

void clearVisited(Graph* graph) //방문 여부를 초기화하는 clearVisited 함수 정의
{
    for (int i = 0; i < MAX_VERTICES; i++) //i가 0부터 MAX_VERTICES(10)보다 작을 때까지 반복
    {
        graph->visited[i] = 0; //graph의 visited[i]에 0 할당..
    }
}