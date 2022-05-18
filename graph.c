#include<assert.h>
#include<stdlib.h>
#include"graph.h"

graph* new_graph() {
	graph* g = (graph*) malloc( 1 *sizeof( graph ) );
	// TODO: handle malloc failiures
	g->edges_size = 3;
	g->edges = (name*) malloc( g->edges_size *sizeof( name ) );
	g->edges_fill = 0;
	
	g->data_size = 20;
	g->data = (type*) malloc( g->data_size *sizeof( type ) );
	g->data_fill = 0;
	
	return g;
}

name add_node( graph* g, type data ) {
	
	if ( !(g->data_fill < g->data_size) ) {
		g->data_size += 20;
		g->data = (type*) realloc( g->data, g->data_size *sizeof( type ) );
		
		assert(g->data == NULL); // TODO: properly handle this case
	}
	
	g->data[ g->data_fill ] = data;
	g->data_fill++;

	return g->data_fill-1;
}

void add_edge( graph* g, name A, name B ) {
	assert( A < g->data_fill && B < g->data_fill ); // TODO: properly handle this case

	if ( g->edges_fill == 0 ) {
		// TODO: figure out if below if statement is redundant
		if ( g->edges_fill+3 > g->edges_size ) {
			g->edges_size = g->edges_fill+3;
			g->edges = (name*) realloc( g->edges, g->edges_size *sizeof( name ) );
			// TODO: handle realloc failure
		}
		
		g->edges[ 0 ] = A;
		g->edges[ 1 ] = B;
		g->edges[ 2 ] = A; // cuz bidirectional graph
		g->edges_fill = 3;
	} else {
		
		// make sure either A or B exist in the path
		int flag = -1; // flag for index of A or B in g->edges
		for ( size_t i = g->edges_fill-1; i >= 0; i-- ) { // logicaly i>0 might work too
			if ( g->edges[ i ] == A || g->edges[ i ] == B ) {
				flag = i;
				break; // TODO: is break fine here?
			}
		}

		if ( flag == -1 ) {
			// TODO: handle it nicely
			return;
		}
		// make sure g->edges has enough allocated space
		if ( g->edges_fill+2 > g->edges_size ) { // TODO: +2 or +1
			g->edges_size = g->edges_fill+2;
			g->edges = (name*) realloc( g->edges, g->edges_size *sizeof( name ) );
			// TODO: handle realloc failure
		}		
	
		// shift all elements after A or B of path by 2 to the left
		for ( size_t i = g->edges_fill-1; i > flag; i-- ) {
			g->edges[ i+2 ] = g->edges[ i ];	
		}
		g->edges_fill += 2;
		
		// insert BA or AB so that its ABA or BAB to path
		g->edges[ flag+1 ] = (g->edges[ flag ] == A) ? B : A;
		g->edges[ flag+2 ] = g->edges[ flag ];

	}

	return;
}

void remove_edge( graph* g, name A, name B ) {
	// TODO: :( not yet implemented
	return;
}

void free_graph( graph* g ) {
	if ( g == NULL ) return;

	if ( g->edges != NULL ) {
	       free( g->edges );
	}
	if ( g->data != NULL ) {
		free( g->data );
	}
		
	free( g );
	return;
}


type get_data( graph* g, name n ) {
	return g->data[n];
}

void print_trivial_paths( graph* g, name start, name end ) {

	// locate first occourance of 'start' in g->edges
	size_t st_index;
	for ( st_index = 0; g->edges[st_index] != start; st_index++ ) {
		if ( st_index+1 >= g->edges_fill ) {
			// 'start' does not exist in g->edges TODO: handle it
			return;
		}
	}
	assert( g->edges[ st_index ] == start ); // TODO: remove later
	

	name* path = (name*) malloc( get_node_count( g ) *sizeof(name) );
	int* map = (int*) calloc( get_node_count( g ), sizeof(name) );
       	name* path_iter = path;
	
	path[ 0 ] = start;
	path_iter++;
	map[ start ] = 1;
	for ( size_t i = st_index +1; i != st_index; i = (i+1) % g->edges_fill ) {
		
		if ( map[g->edges[ i ]] != 0 ) {
			while ( *(path_iter-1) != g->edges[ i ] ) {
				path_iter--;
				map[ *path_iter ]--; // back to zero????
			}

		} else {
			*(path_iter++) = g->edges[ i ];
			map[g->edges[ i ]] = 1;

			if ( g->edges[ i ] == end ) {
				// print path
				for ( size_t i = 0; i < path_iter - path; i++ ) {
					printf( "%zu ", path[i] );
				}
				printf( "\n" );
			
				 
			
			}
		}

	}


	free( path );
	free( map );

	return;
}

size_t get_node_count( graph* g ) {
	return g->data_fill;
}







