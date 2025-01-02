#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class System
{
private:
    // OBJECTS ......................................................
    class Dish
    {
    public:
        int id;
        string name;
        int price;
        // more specification

        Dish(int id_, string name_, int price_)
        {
            id = id_;
            name = name_;
            price = price_;
        }
    };

    class Table
    {
    public:
        int id;
        bool status; // occupied
        int capacity;

        Table(int id_, int capacity_)
        {
            id = id_;
            capacity = capacity_;
            status = false;
        }
    };

public:
    // VALUES ....................................................
    // static
    map<int, Table *> idMap;         // id and tables  ONLY UPDATE IF ADDED OR DELETE TABLE
    map<int, Dish *> idMapDish;      // id and dishes  ONLY UPDATE IF ADDED OR DELETE DISHES
    set<int> allTables;              // all tables ONLY UPDATE IF ADDED OR DELETE TABLE
    set<int> sizes;                  // table sizes available  ONLY UPDATE IF ADDED OR DELETE TABLE
    map<int, set<int>> sizeTableMap; // all table with size  ONLY UPDATE IF ADDED OR DELETE TABLE

    // dynamic
    map<int, queue<int>> freeTables; // size of table and available table in queues

    // REFRESH ............................................
    void Refresh()
    {
        for (auto id : allTables)
        {
            Table *table = idMap[id];
            sizes.insert(table->capacity);
            sizeTableMap[table->capacity].insert(id);
            if (!table->status)
            {
                freeTables[table->capacity].push(id);
            }
        }
    }

    // READ FUNCTIONS......................................
    bool checkStatus(int id)
    {
        Table *table = idMap[id];
        if (table->status)
        {
            cout << "occupied" << endl;
        }
        else
        {
            cout << "empty" << endl;
        }
        return table->status;
    }

    // return all table ids
    vector<int> allTableIds()
    {
        vector<int> alltablesVector;
        for (auto id : allTables)
        {
            cout << id << endl;
            alltablesVector.push_back(id);
        }
        return alltablesVector;
    }

    // ADD OBJECTS ......................................
    void addTable(int id, int capacity)
    {
        if (idMap[id] != NULL)
        {
            cout << "table already exist";
            return;
        }

        Table *table = new Table(id, capacity);

        // update values
        idMap[id] = table;
        allTables.insert(id);
        sizes.insert(capacity);
        sizeTableMap[capacity].insert(id);
    }

    void addDish(int id, string name, int price)
    {
        if (idMapDish[id] != NULL)
        {
            cout << "dish already exist";
            return;
        }
        idMapDish[id] = new Dish(id, name, price);
    }

    // DELETE TABLE ......................................
    void deleteTable(int id)
    {
        if (idMap.find(id) == idMap.end())
        {
            cout << "Table does not exist." << endl;
            return;
        }

        Table *table = idMap[id];
        int capacity = table->capacity;

        // Remove table from all data structures
        allTables.erase(id);
        sizes.erase(capacity);
        sizeTableMap[capacity].erase(id);

        if (!table->status)
        {
            // Remove from freeTables queue if unoccupied
            queue<int> &q = freeTables[capacity];
            queue<int> newQ;
            while (!q.empty())
            {
                int current = q.front();
                q.pop();
                if (current != id)
                {
                    newQ.push(current);
                }
            }
            freeTables[capacity] = newQ;
        }

        // Deallocate memory
        delete table;
        idMap.erase(id);

        cout << "Table " << id << " deleted successfully." << endl;
    }

    // DELETE DISH ......................................
    void deleteDish(int id)
    {
        if (idMapDish.find(id) == idMapDish.end())
        {
            cout << "Dish does not exist." << endl;
            return;
        }

        Dish *dish = idMapDish[id];

        // Deallocate memory
        delete dish;
        idMapDish.erase(id);

        cout << "Dish " << id << " deleted successfully." << endl;
    }

    // FREE TABLE .................................
    void tableFree(int id)
    {
        Table *table = idMap[id];
        table->status = false;
        int size = table->capacity;
        freeTables[size].push(id);
    }

    // ALLOCATE TABLE ...................................
    int allocateTable(int size)
    {
        if (freeTables[size].empty())
        {
            cout << "unavailable" << endl;
            return -1;
        }
        else
        {
            return freeTables[size].front(); // return table id
        }
    }

    // INITIALIZE SYSTEM ...........................................
    System()
    {
        addDish(1, "Roti", 10);
        addDish(2, "Sev", 100);
        for (int i = 0; i < 10; i++)
        {
            addTable(i, 4);
        }
    }
};

int main()
{
    System *temp = new System();

    delete temp; // Clean up the system

    return 0;
}
