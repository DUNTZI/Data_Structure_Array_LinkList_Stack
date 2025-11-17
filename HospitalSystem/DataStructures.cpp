#include "DataStructures.hpp"
#include <iostream>
#include <iomanip> // For formatting output

// ----------------------------------------------------------------------------
// PatientQueue Implementation
// ----------------------------------------------------------------------------

PatientQueue::PatientQueue() : front(nullptr), rear(nullptr) {}

PatientQueue::~PatientQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool PatientQueue::isEmpty() {
    return front == nullptr;
}

void PatientQueue::enqueue(Patient patient) {
    PatientNode* newNode = new PatientNode{patient, nullptr};
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    std::cout << "Patient " << patient.name << " admitted and added to queue.\n";
}

bool PatientQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "No patients in the queue to discharge.\n";
        return false;
    }
    PatientNode* temp = front;
    Patient dischargedPatient = temp->data;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    std::cout << "Patient " << dischargedPatient.name << " (ID: " << dischargedPatient.id
              << ") has been discharged.\n";
    return true;
}

void PatientQueue::display() {
    if (isEmpty()) {
        std::cout << "The patient queue is currently empty.\n";
        return;
    }
    std::cout << "\n--- Current Patient Queue (First to Last) ---\n";
    std::cout << std::left << std::setw(10) << "ID" << std::setw(25) << "Name" << "Condition\n";
    std::cout << "--------------------------------------------------\n";
    PatientNode* temp = front;
    while (temp != nullptr) {
        std::cout << std::left << std::setw(10) << temp->data.id
                  << std::setw(25) << temp->data.name
                  << temp->data.condition << "\n";
        temp = temp->next;
    }
    std::cout << "--------------------------------------------------\n";
}

// ----------------------------------------------------------------------------
// SupplyStack Implementation
// ----------------------------------------------------------------------------

SupplyStack::SupplyStack() : top(nullptr) {}

SupplyStack::~SupplyStack() {
    while (!isEmpty()) {
        pop();
    }
}

bool SupplyStack::isEmpty() {
    return top == nullptr;
}

void SupplyStack::push(Supply supply) {
    SupplyNode* newNode = new SupplyNode{supply, top};
    top = newNode;
    std::cout << "Supply " << supply.type << " (Batch: " << supply.batch
              << ") added to stock.\n";
}

bool SupplyStack::pop() {
    if (isEmpty()) {
        std::cout << "No supplies in the stack to use.\n";
        return false;
    }
    SupplyNode* temp = top;
    Supply usedSupply = temp->data;
    top = top->next;
    delete temp;
    std::cout << "Used 'Last Added' Supply:\n";
    std::cout << "  Type: " << usedSupply.type << "\n";
    std::cout << "  Batch: " << usedSupply.batch << "\n";
    std::cout << "  Quantity: " << usedSupply.quantity << "\n";
    return true;
}

void SupplyStack::display() {
    if (isEmpty()) {
        std::cout << "The supply stock is currently empty.\n";
        return;
    }
    std::cout << "\n--- Current Supply Stock (Top to Bottom) ---\n";
    std::cout << std::left << std::setw(20) << "Type" << std::setw(15) << "Batch" << "Quantity\n";
    std::cout << "--------------------------------------------------\n";
    SupplyNode* temp = top;
    while (temp != nullptr) {
        std::cout << std::left << std::setw(20) << temp->data.type
                  << std::setw(15) << temp->data.batch
                  << temp->data.quantity << "\n";
        temp = temp->next;
    }
    std::cout << "--------------------------------------------------\n";
}

// ----------------------------------------------------------------------------
// EmergencyPriorityQueue Implementation
// ----------------------------------------------------------------------------

EmergencyPriorityQueue::EmergencyPriorityQueue() : head(nullptr) {}

EmergencyPriorityQueue::~EmergencyPriorityQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool EmergencyPriorityQueue::isEmpty() {
    return head == nullptr;
}

void EmergencyPriorityQueue::enqueue(EmergencyCase ec) {
    EmergencyNode* newNode = new EmergencyNode{ec, nullptr};

    if (isEmpty() || ec.priority < head->data.priority) {
        newNode->next = head;
        head = newNode;
    } else {
        EmergencyNode* temp = head;
        while (temp->next != nullptr && temp->next->data.priority <= ec.priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    std::cout << "Logged emergency case for " << ec.patientName
              << " with priority " << ec.priority << ".\n";
}

bool EmergencyPriorityQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "No pending emergency cases.\n";
        return false;
    }
    EmergencyNode* temp = head;
    EmergencyCase criticalCase = temp->data;
    head = head->next;
    delete temp;

    std::cout << "Processing Most Critical Case:\n";
    std::cout << "  Patient: " << criticalCase.patientName << "\n";
    std::cout << "  Type: " << criticalCase.emergencyType << "\n";
    std::cout << "  Priority: " << criticalCase.priority << "\n";
    return true;
}

void EmergencyPriorityQueue::display() {
    if (isEmpty()) {
        std::cout << "The emergency queue is currently empty.\n";
        return;
    }
    std::cout << "\n--- Pending Emergency Cases (Highest Priority First) ---\n";
    std::cout << std::left << std::setw(10) << "Priority" << std::setw(25) << "Patient Name" << "Emergency Type\n";
    std::cout << "---------------------------------------------------------\n";
    EmergencyNode* temp = head;
    while (temp != nullptr) {
        std::cout << std::left << std::setw(10) << temp->data.priority
                  << std::setw(25) << temp->data.patientName
                  << temp->data.emergencyType << "\n";
        temp = temp->next;
    }
    std::cout << "---------------------------------------------------------\n";
}


// ----------------------------------------------------------------------------
// AmbulanceCircularQueue Implementation
// ----------------------------------------------------------------------------

AmbulanceCircularQueue::AmbulanceCircularQueue() : front(-1), rear(-1), count(0) {}

bool AmbulanceCircularQueue::isEmpty() {
    return count == 0;
}

bool AmbulanceCircularQueue::isFull() {
    return count == MAX_AMBULANCES;
}

void AmbulanceCircularQueue::enqueue(Ambulance ambulance) {
    if (isFull()) {
        std::cout << "Ambulance fleet is full. Cannot register more.\n";
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX_AMBULANCES;
    ambulances[rear] = ambulance;
    count++;
    std::cout << "Ambulance " << ambulance.licensePlate << " registered for duty.\n";
}

Ambulance AmbulanceCircularQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "No ambulances on duty to rotate.\n";
        return Ambulance{"", ""}; // Return empty ambulance
    }
    Ambulance rotatedAmbulance = ambulances[front];
    front = (front + 1) % MAX_AMBULANCES;
    count--;
    if (isEmpty()) { 
        front = -1;
        rear = -1;
    }
    return rotatedAmbulance;
}

void AmbulanceCircularQueue::display() {
    if (isEmpty()) {
        std::cout << "No ambulances currently on duty.\n";
        return;
    }
    std::cout << "\n--- Current Ambulance Rotation (Front to Rear) ---\n";
    std::cout << std::left << std::setw(20) << "License Plate" << "Driver Name\n";
    std::cout << "----------------------------------------------\n";
    int i = front;
    for (int j = 0; j < count; j++) {
        std::cout << std::left << std::setw(20) << ambulances[i].licensePlate
                  << ambulances[i].driverName << "\n";
        i = (i + 1) % MAX_AMBULANCES;
    }
    std::cout << "----------------------------------------------\n";
}