#include<stddef.h>

#define name size_t // type in which the names of the nodes will be in, has to be unsigned int
#define type int // type of the data that will be paired with each node


/* 
 * name* edges: array of "name" representing a path that solves the chinese postman
 * problem for the represented graph.
 *
 * type* data: array of "data" whoose elements are data that are assigned to each of the nodes
 *
 */
struct graph {
	name* edges;
	size_t edges_size; // size of allocated area for edges
	size_t edges_fill; // index of next empty element in edges
	type* data;
	size_t data_size; // siza of allocated area for data
	size_t data_fill; // index of next empty element in data
};
typedef struct graph graph;

/* 
 * returns newly allocated graph with initialized attributes
 */
graph* new_graph();

/*
 * adds node to the graph "g" paired with the "data" passed as an argument,
 * returns: the name the given to the new node.
 *
 */
name add_node( graph* g, type data );

/*
 * adds edge to graph "g" connecting node named "A" and node named "B"
 */
void add_edge( graph* g, name A, name B );

/* Frees allocated memory of a graph* g
 */
void free_graph( graph* g );

/* 
 * returns data paired with node named 'n'
 */
type get_data( graph* g, name n );

/* get_node_count returns number of nodes in graph */
size_t get_node_count( graph* g );

/* removes an edge from the graph */
void remove_edge( graph* g, name A, name B );


/* TODO: is_connected_graph() function, returns if the graph represented is a connected one
 */
