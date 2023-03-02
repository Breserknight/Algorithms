#include<iostream>
#include<set>
#include<stack>

class linked_list {
    private:
        long long node_number, direct_distance;
    public:
        linked_list* next, *end;
        /* 
        'this->end' is only for HEAD nodes 
        */
        linked_list(long long value, long long dist) {
            node_number = value;
            direct_distance = dist;
            next = NULL;
            end = NULL;
        }

        linked_list(){
            node_number = -1;
            next = NULL;
            end = this;
        }

        void set_node_number(long long num) {
            node_number = num;
        }

        void append(linked_list* node) {
            next = node;
        }

        linked_list* get_end() {
            return end;
        }

        void set_end( linked_list* end_node ) {
            end = end_node->next;
        }

        void print(){
            linked_list* current_node = this->next;
            /* start from 'next' node to avoid printing the HEAD node */
            while( current_node ) {
                std::cout << "( " << current_node->node_number << ", " << current_node->direct_distance <<" ) ";
                current_node = current_node->next;
            }
            std::cout << "\n";
        }

        long long first(){
            return node_number;
        }

        long long second(){
            return direct_distance;
        }

        void update_distance(long long dist) {
            direct_distance = dist;
        }
};

class Grid {
    private:
        long long number_of_nodes, infinity = __LONG_LONG_MAX__;
        linked_list *grid;
    public:
        Grid(long long n) {
            number_of_nodes = n;
            grid = new linked_list[10];

            read_grid();
            // print();
        }

        void read_grid() {
            std::cout << "ENTER THE GRID MATRIX" << "\n";
            long long _temp;
            for(long long row = 0; row < number_of_nodes ; ++row ) {
                grid[row].set_node_number(row);
                for(long long col = 0; col < number_of_nodes ; ++col ) {
                    std::cin >> _temp;
                    if(row == col || !_temp) continue;
                    grid[row].get_end()->append(new linked_list(col, _temp));
                    grid[row].set_end(grid[row].get_end());
                }
            }
        }

        void print() {
            for(long long row = 0; row < number_of_nodes; row++) {
                std::cout << row << " : ";
                grid[row].print();
            }
        }

        void find_shortest_distance( long long source ) {
            if(source < 0 || source >= number_of_nodes ) return;

            auto cmp = [](linked_list a, linked_list b){ return a.second() < b.second(); };

            std::multiset<linked_list, decltype(cmp)> min_heap(cmp);
            bool visited[number_of_nodes] = {};
            long long distance[number_of_nodes];
            long long path[number_of_nodes] = {};

            for(long long i = 0; i < number_of_nodes; i++) distance[i] = infinity;
            
            distance[source] = 0;
            path[source] = -1;

            min_heap.insert(grid[source]);

            while(!min_heap.empty()) {
                // pop 
                linked_list selected = *min_heap.begin();

                long long node_val = selected.first();

                visited[node_val] = 1;
                
                min_heap.erase(min_heap.begin());

                for(linked_list* node = grid[node_val].next; node; node = node->next) {
                    // std::cout << distance[node->first()] <<  " " <<  distance[node_val] + node->second() << "\n";
                    if(!visited[node->first()] && distance[node->first()] > distance[node_val] + node->second() ) {
                        distance[node->first()] = distance[node_val] + node->second();
                        min_heap.insert(*node);
                        path[node->first()] = node_val;
                    }
                }
            }

            // for(auto i: path) std::cout << i << " ";
            // std::cout << "\n";

            std::cout << ": Shortest Distance :" << "\n";
            for(long long i = 0, temp; i < number_of_nodes ; i++) {
                std::cout << "Distance from " << source << " to " << i << " : " << distance[i] << "; Path : ";
                std::stack<long long> st;
                temp = i;
                while(temp != -1) st.push(temp), temp = path[temp];
                
                while(!st.empty()) {
                    std::cout << st.top();
                    st.pop();
                    if(!st.empty()) std::cout << " -> "; 
                }
                std::cout << "\n";
            }
        }
};

int main(){
    Grid *g = new Grid(5);
    g->find_shortest_distance(0);
}



/*
i/p
0  5  1  4  0
1  0  7  8  1
0  3  0  6  7
0  0  0  0  0
0  0  0  4  0
*/