#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define BUFFER_LIMIT 100000
#define LIMITED_LIMIT 1024

int lineCount=0, colCount=0, wc=0;
int pos = 0;
char LOG[LIMITED_LIMIT];
char SEARCH_STRING[LIMITED_LIMIT];
char SEARCH_DATA[BUFFER_LIMIT];
char current_search_buffer[LIMITED_LIMIT];
int prev_line_no = 0; 
int prev_col_no = 0;
int state = 0;
char * currentFilePath;

char search_string[] = "nodes";
char search_base[] = "An nodes artificial neural network is an interconnected group of nodes, akin to the vast network of neurons in a brain. Here, each circular node represents an artificial neu \
 ron and an arrow represents a connection from the output of one neuron to the input of another.";

int no_of_states; // will be initialized in init_dfa()
int current_state;
int * transitions; // Will be initialized in init_dfa()
int no_of_transitions;
int start_state;
int final_state;
struct DFA_state{
    int state_no;
    char transition_character;
    int transit_to;
    int trap_state;
};
typedef struct DFA_state DFA_state;

DFA_state * states;

void init_dfa();
void build_transition_table();
void start_dfa();
void reset_dfa();
void transit(char ch);
int is_final_state();

void log_data(char * found_string, int line_no, int col_no);
int found();
int size_of(char * s);

void set_data(const char * str);
char * get_data();

void set_string(const char * str);
char * get_string();

void init_dfa()
{
    no_of_states = size_of(get_string()) + 1; // +1 for the trap state
    transitions = (int *)malloc(sizeof(int) * no_of_states);
    no_of_transitions = 0;
    start_state = 0;
    final_state = no_of_states - 1;
    current_state = 0;
    transitions[0] = current_state;
}

void build_transition_table()
{
    int counter = 0;
    int i;
    int string_size =  size_of(get_string());
    char * searching_string = get_string(); 
    states = (DFA_state *)malloc(sizeof(DFA_state) * no_of_states);

    while(*searching_string != '\0')
    {
    if(counter < string_size)
    {
        states[counter].state_no = counter;
        states[counter].transition_character = *searching_string;
        states[counter].transit_to = counter+1;
        states[counter].trap_state = no_of_states;
    }
    searching_string++;
    counter++;
    }
    
    
    /*for(i=0; i<no_of_states-1; i++)
    {
        printf("%d -> State no is %d.\n", i, states[i].state_no);
        printf("%d -> Transition_character is %c.\n", i, states[i].transition_character);
        printf("%d -> Transit_no is %d.\n", i, states[i].transit_to);
        printf("%d -> Trap state is %d.\n", i, states[i].trap_state);
    }*/
}

void start_dfa()
{
    char * searching_data = get_data();
    int col_no = 0, line_no = 0, cc = 0;
    while(*searching_data != '\0')
    {
transit(*searching_data);
if(is_final_state())
{
    log_data(searching_data, line_no, (col_no - size_of(get_string()) + 1));
    reset_dfa();
}
searching_data++;

if(*searching_data == '\n'){
    col_no = 0;
    line_no++;
}
col_no++;
cc++;
    }
    if(*searching_data == '\0') { reset_dfa(); }
}

void reset_dfa()
{
free(transitions);
init_dfa();
}

void transit(char ch)
{
    DFA_state current_dfa_state = states[current_state];
    if(current_dfa_state.transition_character == tolower(ch) || current_dfa_state.transition_character == toupper(ch))
    {
current_state = current_dfa_state.transit_to;
//printf("Transition to %d.\n", current_state);
no_of_transitions++;
transitions[no_of_transitions] = current_state;
    }else{
current_state = current_dfa_state.trap_state;
//printf("Resetting.\n");
reset_dfa();
    }   
}

int is_final_state()
{
    if(current_state == final_state)
    {
return 1;
    }else{
return 0;
    }
}

void log_data(char * found_string, int line_no, int col_no)
{
printf("The search string was found in file %s at line no %d and column no %d.\n", "REPLACE WITH PATH", line_no, col_no);
//strcpy(LOG, "The search string was found in file ");
//strcpy(LOG, file_path);
//strcpy(LOG, " at line no ");
//strcpy(LOG, (char)(line_no+'0'));
//strcpy(LOG, " at col no ");
//strcpy(LOG, (char)(col_no+'0'));
}

int size_of(char * s)
{
    int count = 0;
    while(*s != '\0'){
count++;
s++;
    }
    return count;
}

void set_string(const char * str)
{
    char * string = SEARCH_STRING;
    while(*str != '\0')
    {
*(string++) = *(str++);
    }
}

char * get_string()
{
    char * string = SEARCH_STRING;
    if(*string != '\0') // statement to check if SEARCH_STRING an empty string
        return SEARCH_STRING;
    else
        return NULL;
}

void set_data(const char * str)
{
    char * string = SEARCH_DATA;
    while(*str!='\0')
{
        *(string++) = *(str++);
    }
}

char * get_data()
{
    char * string = SEARCH_DATA;
    if(*string != '\0') // statement to check if SEARCH_STRING an empty string
        return SEARCH_DATA;
    else
        return NULL;
}

int simulate_lex(const char * path_of_file, const char * searching_data, const char * searching_string)
{
//char search_string[] = "nodes";
//char search_base[] = "An artificial neural network is an interconnected group of nodes, akin to the vast network of neurons in a brain. Here, each circular node represents an artificial neuron and an arrow represents a connection from the output of one neuron to the input of another.";
set_data(searching_data);
set_string(searching_string);
//simulate_lex();
printf("--------------------NEW SEARCH--------------------\n");
printf("DATA : %s\n", get_data());
printf("SEARCH_FOR : %s\n", get_string());

init_dfa();
build_transition_table();
start_dfa();
return 0;
}
