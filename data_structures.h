#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <type_traits>
using namespace std;

// ============================================
// COMMON STRUCTURES
// ============================================

struct Citizen {
    int id;
    string name;
    int age;
    string cnic;
    string phone;
    string address;
};

struct Complaint {
    int complaintId;
    string citizenName;
    string complaintType;
    string area;
    string description;
    int priority; // For priority queue
};

struct Hospital {
    int hospitalId;
    int patientId;
    string patientName;
    string doctorName;
    string disease;
    int billAmount;
};

struct Traffic {
    int violationId;
    string vehicleNumber;
    string driverName;
    string violationType;
    int fineAmount;
};

struct Utility {
    int utilityId;
    string utilityType;
    string consumerName;
    int units;
    int billAmount;
};

// ============================================
// BINARY SEARCH TREE (BST) NODE
// ============================================

template <typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// ============================================
// LINKED LIST NODE
// ============================================

template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    
    ListNode(T val) : data(val), next(nullptr) {}
};

// ============================================
// HASH TABLE NODE
// ============================================

template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;
    
    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

// ============================================
// GRAPH NODE (Adjacency List)
// ============================================

struct GraphNode {
    int vertex;
    string location;
    vector<pair<int, int>> neighbors; // (vertex, distance)
    
    GraphNode(int v, string loc) : vertex(v), location(loc) {}
};

// ============================================
// BINARY SEARCH TREE CLASS
// ============================================

template <typename T>
class BinarySearchTree {
private:
    BSTNode<T>* root;
    
    BSTNode<T>* insertHelper(BSTNode<T>* node, T data) {
        if (node == nullptr) {
            return new BSTNode<T>(data);
        }
        if (data.id < node->data.id) {
            node->left = insertHelper(node->left, data);
        } else if (data.id > node->data.id) {
            node->right = insertHelper(node->right, data);
        }
        return node;
    }
    
    BSTNode<T>* searchHelper(BSTNode<T>* node, int id) {
        if (node == nullptr || node->data.id == id) {
            return node;
        }
        if (id < node->data.id) {
            return searchHelper(node->left, id);
        }
        return searchHelper(node->right, id);
    }
    
    BSTNode<T>* findMin(BSTNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    BSTNode<T>* deleteHelper(BSTNode<T>* node, int id) {
        if (node == nullptr) return node;
        
        if (id < node->data.id) {
            node->left = deleteHelper(node->left, id);
        } else if (id > node->data.id) {
            node->right = deleteHelper(node->right, id);
        } else {
            if (node->left == nullptr) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            
            BSTNode<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data.id);
        }
        return node;
    }
    
    void inOrderHelper(BSTNode<T>* node, vector<T>& result) {
        if (node != nullptr) {
            inOrderHelper(node->left, result);
            result.push_back(node->data);
            inOrderHelper(node->right, result);
        }
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    void insert(T data) {
        root = insertHelper(root, data);
    }
    
    T* search(int id) {
        BSTNode<T>* node = searchHelper(root, id);
        return (node != nullptr) ? &(node->data) : nullptr;
    }
    
    void remove(int id) {
        root = deleteHelper(root, id);
    }
    
    vector<T> inOrderTraversal() {
        vector<T> result;
        inOrderHelper(root, result);
        return result;
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
    
    int getHeight(BSTNode<T>* node) {
        if (node == nullptr) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
    
    int getHeight() {
        return getHeight(root);
    }
};

// ============================================
// HASH TABLE CLASS
// ============================================

template <typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 101;
    HashNode<K, V>* table[TABLE_SIZE];
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }
    
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    void insert(K key, V value) {
        int index;
        if constexpr (is_same_v<K, int>) {
            index = hashFunction(key);
        } else {
            index = hashFunction(string(key));
        }
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }
    
    V* search(K key) {
        int index;
        if constexpr (is_same_v<K, int>) {
            index = hashFunction(key);
        } else {
            index = hashFunction(string(key));
        }
        HashNode<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void remove(K key) {
        int index;
        if constexpr (is_same_v<K, int>) {
            index = hashFunction(key);
        } else {
            index = hashFunction(string(key));
        }
        HashNode<K, V>* current = table[index];
        HashNode<K, V>* prev = nullptr;
        
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

// ============================================
// PRIORITY QUEUE (Min Heap)
// ============================================

class PriorityQueue {
private:
    vector<Complaint> heap;
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].priority >= heap[parent].priority) {
                break;
            }
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < heap.size() && heap[left].priority < heap[smallest].priority) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].priority < heap[smallest].priority) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    void enqueue(Complaint c) {
        heap.push_back(c);
        heapifyUp(heap.size() - 1);
    }
    
    Complaint dequeue() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty");
        }
        Complaint top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
        return top;
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
};

// ============================================
// GRAPH CLASS (Adjacency List)
// ============================================

class CityGraph {
private:
    vector<GraphNode*> vertices;
    int vertexCount;
    
public:
    CityGraph() : vertexCount(0) {}
    
    void addVertex(int id, string location) {
        vertices.push_back(new GraphNode(id, location));
        vertexCount++;
    }
    
    void addEdge(int from, int to, int distance) {
        if (from < vertices.size() && to < vertices.size()) {
            vertices[from]->neighbors.push_back({to, distance});
            vertices[to]->neighbors.push_back({from, distance}); // Undirected
        }
    }
    
    vector<int> shortestPath(int start, int end) {
        vector<int> dist(vertexCount, INT_MAX);
        vector<int> parent(vertexCount, -1);
        vector<bool> visited(vertexCount, false);
        
        dist[start] = 0;
        
        for (int i = 0; i < vertexCount; i++) {
            int u = -1;
            for (int j = 0; j < vertexCount; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }
            
            if (u == -1 || dist[u] == INT_MAX) break;
            visited[u] = true;
            
            for (auto& neighbor : vertices[u]->neighbors) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
        
        vector<int> path;
        if (dist[end] != INT_MAX) {
            int current = end;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
        }
        return path;
    }
    
    void displayGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            cout << "\nVertex " << i << " (" << vertices[i]->location << "): ";
            for (auto& neighbor : vertices[i]->neighbors) {
                cout << "-> " << neighbor.first << " (dist: " << neighbor.second << ") ";
            }
        }
    }
};

// ============================================
// SORTING ALGORITHMS
// ============================================

class SortingAlgorithms {
public:
    // Quick Sort
    template <typename T>
    static void quickSort(vector<T>& arr, int low, int high, bool (*compare)(T, T)) {
        if (low < high) {
            int pi = partition(arr, low, high, compare);
            quickSort(arr, low, pi - 1, compare);
            quickSort(arr, pi + 1, high, compare);
        }
    }
    
    template <typename T>
    static int partition(vector<T>& arr, int low, int high, bool (*compare)(T, T)) {
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (compare(arr[j], pivot)) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    // Merge Sort
    template <typename T>
    static void mergeSort(vector<T>& arr, int left, int right, bool (*compare)(T, T)) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, compare);
            mergeSort(arr, mid + 1, right, compare);
            merge(arr, left, mid, right, compare);
        }
    }
    
    template <typename T>
    static void merge(vector<T>& arr, int left, int mid, int right, bool (*compare)(T, T)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<T> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (compare(L[i], R[j])) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
        
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }
};

#endif // DATA_STRUCTURES_H

