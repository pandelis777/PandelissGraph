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

	/*  get path form g->edges[ g->edges_fill-1 ] to A or B and
	 *  append it to path and then append its reverse path.
	 */


	if ( g->edges_fill == 0 ) {
		// TODO: figure out if below if statement is redundant
		if ( g->edges_fill+2 > g->edges_size ) {
			g->edges_size = g->edges_fill+2;
			g->edges = (name*) realloc( g->edges, g->edges_size *sizeof( name ) );
			// TODO: handle realloc failure
		}
		
		g->edges[ 0 ] = A;
		g->edges[ 1 ] = B;
		g->edges_fill = 2;
	} else {
		
		void* tmp = NULL; 		
				
		for ( size_t i = g->edges_fill-2; g->edges[ i+1 ] != A && g->edges[ i+1 ] != B; i-- ) {
			
			if ( g->edges_fill >= g->edges_size ) {
				g->edges_size = g->edges_fill +20;
				
				tmp = realloc( g->edges, g->edges_size *sizeof( name ) );
				if ( tmp == NULL ) {
					fprintf( stderr, "Failed to reallocate g->edges memory block" );
					return; // TODO: properly handle the exit case
				} else {
					g->edges = tmp;
				}
			}

			assert( g->edges_fill < g->edges_size );

			g->edges[ g->edges_fill ] = g->edges[ i ];
			g->edges_fill++;
		}

		if ( g->edges_fill >= g->edges_size ) {
			g->edges_size = g->edges_fill +20;
			
			tmp = realloc( g->edges, g->edges_size *sizeof( name ) );
			if ( tmp == NULL ) {
				fprintf( stderr, "Failed to reallocate g->edges memory block" );
				return; // TODO: properly handle the exit case
			} else {
				g->edges = tmp;
			}
		}
		assert( g->edges_fill < g->edges_size );	
		assert( g->edges[ g->edges_fill-1 ] == A || g->edges[ g->edges_fill-1 ] == B );
		
		g->edges[ g->edges_fill ] = (g->edges[ g->edges_fill-1 ] == A) ? B : A;
		g->edges_fill++;	
	}

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


