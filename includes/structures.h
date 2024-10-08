/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/14 17:01:41 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

typedef enum e_mode {
	DEFAULT,
	SILENT,
} t_mode;

struct s_pathes;
struct s_visualiser;
struct s_edge;
struct s_node;
struct s_room;
struct s_ultimate_definitive_edition_deluxe_master_path;

typedef struct s_ultimate_definitive_edition_deluxe_master_path
{
	int	 													size;
	struct s_room											*room;
	struct s_ultimate_definitive_edition_deluxe_master_path *next;
	int 													ants;
}	t_ultimate_definitive_edition_deluxe_master_path;

typedef struct s_node
{
	int														nb_outing_edges;
	int														max_outing_edge_count;
	struct s_edge											**outing_edges;
	struct s_room											*room;

}	t_node;

typedef struct s_edge
{
	short													capacity;
	short													flow;
	short													residual_capacity;
	short													is_reversal_edge;
	struct s_node											*in;
	struct s_node											*out;

	// Resolution
	struct s_edge											*previous_edge;
	short													depth;
}	t_edge;

typedef struct s_path
{
	struct s_edge											*last_edge;
}	t_path;

typedef struct s_graph
{
	// NOTE: for spiiiiider (fast) stuff, might create a data structure for edges to find them by in and out like real fast
	int														nb_edges;
	int														nb_nodes;
	int														max_edge_count;
	int														max_node_count;
	struct s_edge											**edges;
	struct s_node											**nodes;
	struct s_node											*source;
	struct s_node											*sink;
}	t_graph;

typedef struct s_room
{
	// Basic stuff
	char													name[NAME_SIZE + 1];
	int														id;
	int														is_start;
	int														is_end;

	// Tree stuff
	struct s_room											*left;
	struct s_room											*right;

	// visualiser stuff
	int														x_coord;
	int														y_coord;
	int														og_y_coord;
	int														*distances_to_ends;
	int														nb_linked;
	int														max_linked;
	struct s_room											**linked_rooms;

	// Graph stuff
	struct s_node											*in_node;
	struct s_node											*out_node;
}	t_room;

typedef struct s_visualiser
{
	int 													max_y;
	int 													max_x;

	int 													nb_allocated_room_lines;
	int														*room_line_size;

}	t_visualiser;

typedef struct s_ant
{
	t_room													*current_room;
	t_ultimate_definitive_edition_deluxe_master_path		*path;
	int														is_arrived;
} t_ant;

typedef struct s_lem_in
{
	// Options
	int														verbose;
	int														has_visualiser;

	// Counter
	int														nb_rooms;
	int														nb_links;
	int														nb_ants;

	// Room tree
	struct s_room											**rooms;
	struct s_room											*start;
	struct s_room											*end;

	// visualiser
	struct s_visualiser										*visualiser;
	t_ant													*ants;

	// Solve Graph
	struct s_graph											*graph;

}	 t_lem_in;


typedef struct s_queue
{
	int														size;
	int														allocated_space;
	int														first_element_index;
	void													**elements;
} t_queue;

#endif
