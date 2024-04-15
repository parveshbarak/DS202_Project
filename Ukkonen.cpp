#include<bits/stdc++.h>
using namespace std;


typedef struct SuffixTree start_node;
start_node *root;
start_node *latest_node = NULL; 
start_node *active_node = NULL; 

int remaining = 0; 
// active points
int active_edge = -1; 
int active_len = 0; 
int string_size = -1; 
const int alphabet_size = 256;
// #define alphabet_size = 1e8;


//strcture of suffix
struct SuffixTree 
{ 
    struct SuffixTree *nodes[alphabet_size]; 
    struct SuffixTree *suffix_link; 
    int start; 
    int *end; 
    int suffix_index; 
}; 

int global_end = -1;

string input; 


int get_length(start_node *n)
{ 
    return *(n->end) - (n->start) + 1; 
}

// constructor
start_node *new_node(int start, int *end) 
{ 
    start_node *node = new start_node; 
    int i; 
    for (i = 0; i < alphabet_size; i++) 
    {
        node->nodes[i] = NULL; 
    }
    node->suffix_link = root; 
    node->start = start; 
    node->end = end; 
    node->suffix_index = -1; 
    return node; 
} 

int edge_length(start_node *n)
{ 
    return get_length(n) ; 
} 



// 3 rules of extension
void rules_of_extension(int index)
{
    //rule 1
    global_end = index;
    remaining++;
    while(remaining > 0) 
    {
        if (active_len == 0)
        {
        active_edge = index; 
        }
        if (!active_node->nodes[input[active_edge]])
        {
            //rule 2
            active_node->nodes[input[active_edge]] = new_node(index, &global_end);
            if (latest_node)
            {
                latest_node->suffix_link = active_node;
                latest_node = NULL;
            }
        }
        else
        {
            //rule 3 (the show stopper)
            start_node *next = active_node->nodes[input[active_edge]];
            if (active_len >= edge_length(next))
            {
                active_edge++; 
                active_len--; 
                active_node=next; 
                continue;
            } 
            if (input[next->start + active_len] == input[index])
            {
                if(latest_node && active_node != root)
                {
                    latest_node->suffix_link = active_node;
                    latest_node = NULL;
                }
            active_len++;
            break;
            }
            int *split_node = NULL; 
            split_node = new int;
            *split_node = next->start + active_len - 1;
            
            start_node *split = new_node(next->start, split_node);
            
            active_node->nodes[input[active_edge]] = split;

            split->nodes[input[index]] = new_node(index, &global_end);
            
            next->start += active_len;
            
            split->nodes[input[next->start]] = next;

            if (latest_node)
            {
                latest_node->suffix_link = split;
            }
            latest_node = split;
        }
        remaining--;
        if (active_node == root && active_len > 0) 
        {
            active_len--;
            active_edge ++;
        }
        else if (active_node != root) 
        {
            active_node = active_node->suffix_link;
        }
    }
} 

string readFileContent(const string& filename) {
  ifstream inputFile(filename);
  string text;

  if (inputFile.is_open()) {
    // Read the entire file content into a string
    getline(inputFile, text, string::traits_type::to_char_type('\0'));
    inputFile.close();
  } else {
    cerr << "Error opening file: " << filename << endl;
  }

  return text;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Error";
    return 1;
  }

    string filename = argv[1];
    string t = readFileContent(filename);
    // string t;
    //   cout<<"Enter the string"<<endl;
    // cin>>t;

    input=t+'$';
    // cout << input;
    string_size = input.size(); 
    int rootEnd = - 1; 

    auto start = chrono::high_resolution_clock::now();

    root = new_node(-1, &rootEnd); 

    active_node = root;
    
    for (int i=0; i<string_size; i++) 
    {
        rules_of_extension(i); 
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double elapsedTime = static_cast<double>(duration.count()) * chrono::nanoseconds::period::num / chrono::nanoseconds::period::den;

    cout << "Time taken by Ukkonen to construct suffix tree: " << elapsedTime << " seconds" << endl;

    return 0; 
} 