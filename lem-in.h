/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:44:23 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/11 18:31:12 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEM_IN_H

# define LEM_IN_H
# define BUFF_SIZE 65
# define MAX_FD 4865

# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>//a enlever


int				get_next_line(const int fd, char **line);
char			*ft_strnew(size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_isdigit(int c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);

typedef struct	s_filist
{
	char	*line;
	struct	s_filist	*previous;
	struct	s_filist	*next;
}				t_filist;

typedef struct	s_roomlist
{
	int		taken;
	int		way;
	char				**beftunnels;
	char				**tunnels;
	int					place;
	char				*name;
	struct	s_roomlist	*previous;
	struct	s_roomlist	*next;
}				t_roomlist;

typedef struct	s_waylist
{
	char	*name;
	int		way;
	int		place;
	int		ants;
	struct	s_waylist	*previous;
	struct	s_waylist	*next;

}				t_waylist;

typedef struct	s_listlist
{
	struct	s_waylist	*waylist;
	int		ants;
	struct	s_listlist	*previous;
	struct	s_listlist	*next;
}				t_listlist;

typedef struct	s_namelist
{
	char	*name;
	struct s_namelist	*previous;
	struct s_namelist	*next;
}				t_namelist;

typedef struct	s_variables
{

	char        *tmp;
	t_filist    *filist;
	t_filist    *filistart;
	t_roomlist  *roomlist;
	t_roomlist  *roomlistart;
	t_listlist  *listlist;
	t_listlist  *listlistart;
	t_namelist  *namelist;
	t_namelist  *namelistart;
	int         way;

}				t_variables;

void    ft_show_filist(t_filist *filistart);//a enlever dans lem-in.c
void    ft_show_listlist(t_listlist *listlist);//a enlever dans lem-in.c


int     ft_already(char *name, t_namelist *namelistart);
void    ft_ants(t_listlist *listlist, t_filist *filistart);
int     ft_at_least_one_room(char *tmp);
int     ft_bad_room(char *tmp, int step, int i);
char    *ft_beflink(t_filist *filist, t_roomlist *roomlist);
void    ft_build(t_variables *var);
void        ft_build_waylist(t_roomlist *roomlist, t_waylist **waylist, int way, t_roomlist *roomlistart);
int     ft_check_connection(t_roomlist *roomlistart, t_roomlist *roomlist);
int     ft_check_next_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart);
int     ft_check_previous_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart);
void    ft_cpyname(t_filist *filist, t_roomlist *roomlist);
int     ft_disizit(t_filist *filist, t_roomlist *roomlist);
int     ft_disiz_beftunnel(t_filist *filist, t_roomlist *roomlist);
int     ft_disiz_tunnel(t_filist *filist, t_roomlist *roomlist);
t_filist    *ft_filstnew(char *tmp, t_filist *link);
int     ft_firsts_filist_namelist_argc(t_variables *var, int argc);
void    ft_first_listlist(t_variables *var);
void    ft_first_roomlist(t_variables *var);
void    ft_free(t_filist *filistart, t_roomlist *roomlist, t_listlist *listlist, t_namelist *namelist);
void    ft_free_beftunnels(t_roomlist *roomlist);
void    ft_free_filist_namelist(t_filist *filistart, t_namelist *namelist, t_filist *tmp, t_namelist *namelistmp);
void    ft_free_listlist(t_listlist *listlistmp, t_listlist *listlist, t_waylist *waylistmp);
void    ft_free_no_listlist(t_filist *filistart, t_roomlist *roomlist, t_namelist *namelist);
void    ft_free_only_two(t_filist *filistart, t_namelist *namelist);
void    ft_free_roomlist(t_roomlist *roomlistmp, t_roomlist *roomlist);
void    ft_free_tunnels(t_roomlist *roomlist);
void    ft_gnl(t_variables *var);
void    ft_init(t_roomlist *roomlist);
int     ft_is_there_a_way(t_roomlist *roomlistart, int way);
void    ft_length(t_roomlist **roomlist, int way, int *maxplace, t_roomlist *end);
char    *ft_link(t_filist *filist, t_roomlist *roomlist);
void    ft_link_beftunnels(int *i, t_roomlist *roomlist, t_filist *filist, t_filist *filistart);
void    ft_link_tunnels(int *i, t_roomlist *roomlist, t_filist *filist, t_filist *filistart);
void    ft_listlist(t_listlist *listlist, t_roomlist *roomlistart, t_roomlist *roomlist, int way);
t_listlist  *ft_listlistnew(t_listlist *listlist, int way);
void    ft_malloc_beftunnels(t_roomlist *roomlist, t_filist *filist, t_roomlist *roomlistart, t_filist *filistart);
void    ft_malloc_tunnels(t_roomlist *roomlist, t_filist *filist, int *tunnbr, t_filist *filistart);
void    ft_name(t_filist *filist, t_roomlist *roomlist);
t_namelist      *ft_new_name(char *tmp, t_namelist *namelist);
int		ft_not_yet(char *tmp, t_namelist *namelistart);
int		ft_not_yet_first_room(char *tmp, int i, t_namelist *namelist, int ok);
int		ft_not_yet_second_room(char *tmp, int i, t_namelist *namelist, int ok);
int     ft_no_zero(t_roomlist *roomlistart);
void    ft_place(t_filist *filist, t_roomlist* roomlist);
void    ft_place_by_beftunnels(t_roomlist *roomlist, int i, t_roomlist *roomlistart);
void    ft_place_by_tunnels(t_roomlist *roomlist, int i, t_roomlist *roomlistart);
void    ft_place_end(t_filist *filist, t_roomlist *roomlist);
void    ft_place_start(t_filist *filist, t_roomlist *roomlist);
int     ft_possible(t_variables *var);
void    ft_print_anthill(t_filist *filistart);
void    ft_reset(t_roomlist *roomlistart, int way);
int     ft_reverse(t_roomlist *roomlist, int way);
void    ft_roomlist_to_first(t_roomlist **roomlist, t_roomlist *roomlistart);
t_roomlist  *ft_roomlstnew(t_roomlist *roomlist);
void    ft_room_max(t_roomlist *roomlist, t_roomlist **roomax, int maxplace, int way);
void    ft_searching_way(t_roomlist *roomlist, t_roomlist *roomlistart, int way);
int     ft_search_first_reverse(t_roomlist *end, t_roomlist *roomlistart, int way);
int     ft_search_next(t_roomlist *roomlist, t_roomlist *roomlistart, int way);
void    ft_search_other_reverses(t_roomlist *roomlistart, int maxplace, int way);
int     ft_search_previous(t_roomlist *roomlist, t_roomlist *roomlistart, int way);
void    ft_show_roomlist(t_roomlist *roomlist);
void    ft_smallest_biggest(t_roomlist **roomlist, int way, t_roomlist *end, int *maxplace);
int     ft_start_to_end(t_filist *filistart, t_roomlist *roomlist, t_roomlist *roomlistart, int way);
int     ft_step_one(char *tmp, int i, int *step);
int     ft_step_three(char *tmp, int *step, t_namelist *namelistart);
int     ft_step_two(char *tmp, int *step, t_namelist *namelist, t_namelist *namelistart);
void    ft_takens_to_one(t_roomlist *roomlistart, int way);
int     ft_this_is_new_room(t_filist *filist);
void    ft_tunnels(t_filist *filist, t_roomlist *roomlist);
int     ft_valid_line(char *tmp, int check, t_namelist *namelistart);
int     ft_way(t_filist *filist, t_roomlist *roomlist, t_roomlist *roomlistart, int way);
t_waylist   *ft_waylist(t_roomlist *roomlistart, t_roomlist *roomlist, int way);
t_waylist   *ft_waylistnew(t_roomlist *roomlist, int way, t_waylist *waylist);
void        ft_waylist_first(t_waylist *waylist, int way);
void    ft_ways_to_zero(t_roomlist *roomlistart);
void    ft_which_max_and_losts_to_zero(t_roomlist *roomlist, int *max);



#endif
















