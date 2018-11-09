/*
** #### dans item.h #####
*/

typedef enum	e_mat
{
	MAT_COPPER,
	MAT_SILVER,
	MAT_CACA
}				t_mat;

typedef void	(*t_init_func)(t_mat); // function pointer type declaration

class	Item
{
	public :
		Item(t_mat mat);	// constructor
		~Item();			// destructor

	private :
		char	*name;
		t_mat	mat;
		int		weight;
		int		price;
}

/*
** dans item.cpp
*/

// function pointers definitions

int		init_copper(t_mat mat)
{
	// initialize copper items
}

int		init_silver(t_mat mat)
{
	// initialize silver items
}

void	init_caca(t_mat mat)
{
	// initialize caca items
}

// constructor definition

Item::Item(char *item_name, t_mat mat)
{
	t_init_func	init_func[NB_MAT]{
		init_copper,
		init_silver,
		init_caca
	};

	name = strdup(item_name);
	init_func[mat];
}


int	main()
{
	Item something("toilet brush", MAT_CACA);

	return 0;
}