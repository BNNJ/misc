/*
** #### dans item.h #####
*/

typedef enum	e_mat
{
	MAT_COPPER,
	MAT_SILVER,
	MAT_CACA
}				t_mat;

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

int		init_weight(t_mat mat)
{
	// initialise le poids en fonction de mat
}

int		init_price(t_mat mat)
{
	// initialise le prix en fonction de mat
}

Item::Item(char *item_name, t_mat mat)
{
	name = strdup(item_name);
	t_mat = mat; // au cas ou on ai besoin du materiau plus tard
	weight = init_weight(mat);
	price = init_price(mat);
}


int	main()
{
	Item something("toilet brush", MAT_CACA);

	return 0;
}