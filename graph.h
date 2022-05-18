#include<stddef.h>



/*
 * size_t* edges: array of "size_t" representing a path that solves the chinese postman
 * problem for the represented graph.
 *
 * void** data: array of "data" whoose elements are data that are assigned to each of the nodes
 *
 */
struct graph {
	size_t* edges;
	size_t edges_size; // size of allocated area for edges
	size_t edges_fill; // index of next empty element in edges
	void** data;
	size_t data_size; // siza of allocated area for data
	size_t data_fill; // index of next empty element in data
};
void*def struct graph graph;

/*
 * returns newly allocated graph with initialized attributes
 */
graph* new_graph();

/*
 * adds node to the graph "g" paired with the "data" passed as an argument,
 * returns: the size_t the given to the new node.
 *
 */
size_t add_node( graph* g, void* data );

/*
 * adds edge to graph "g" connecting node size_td "A" and node size_td "B"
 */
void add_edge( graph* g, size_t A, size_t B );

/* Frees allocated memory of a graph* g
 */
void free_graph( graph* g );

/*
 * returns data paired with node size_td 'n'
 */
void* get_data( graph* g, size_t n );

/* get_node_count returns number of nodes in graph */
size_t get_node_count( graph* g );

/* removes an edge from the graph */
void remove_edge( graph* g, size_t A, size_t B );


/* TODO: is_connected_graph() function, returns if the graph represented is a connected one
 */
