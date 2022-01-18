#ifndef TERMINAL_BUDGET_TRACKER_TRACKER_FILE_H
#define TERMINAL_BUDGET_TRACKER_TRACKER_FILE_H

#include <stdint.h>
#include <malloc.h>

#define REPLACE 1
#define ADD	2
#define SUB	3

#define FREE_NULL_TERM_ARRAY(ARRAY) do 			\
	{						\
		for (int i = 0; ARRAY[i]; i++)		\
			free(ARRAY[i]);			\
		free(ARRAY);				\
		ARRAY = NULL;				\
	} while (0);

typedef int8_t c_mode;

/**
  @param amount The amount to replace/add/sub.
  @param mode The mode ( replace = 1, add = 2, sub = 3 ).
  @return On success 0. On error -1 is returned.
*/
extern int modify_amount(const char *amount, c_mode mode);

/**
  @param day_spends The amount of money in a day.
  @param date The date of the transaction.
  @return On success 0. On error -1 is returned.
*/
extern int add_day_spend(const char *day_spends, const char *date);


/**
  @param category The category to add the associate merchant.
  @param merchant The merchant to add.
  @return On success 0. On error -1 is returned.
*/
extern int add_merchant_to_category(const char *category, 
				    const char *merchant);

/**
  @param category The category to modify the amount.
  @param amount The amount to repalce/add/sub.
  @param mode The mode ( replace = 1, add = 2, sub = 3 ).
  @retrun On success 0. On error -1 is returned.
*/
extern int modify_category_amount(const char *category, const char *amount,
				  c_mode mode);

/**
  @param new_category The name of the new category.
  @param amount The amout of the category. In case of null 0 is stored.
  @return On success 0. On error -1 is returned. 
*/
extern int add_category(const char *new_category, const char *amount);

/**
  @param category The name of the category to be removed.
  @return On success 0. On error -1 is returned.
*/
extern int remove_category(const char *category);

/**
  @return A malloc pointer tha points to the coresponded value of the amount.
	  The returned value must be freed using the free_amount function.
*/
extern char *get_amount(void);

// Free's the amount.
static inline void free_amount(char *amount)
{
	free(amount);
	amount = NULL;
}

/**
  @param category The category to get.
  @return An array of malloc pointers that has all the elemenets of the array in file.
  	  The returned array must be freed using the free_category function.
*/
extern char **get_category(const char *category);

// Free's the elements of a category.
static inline void free_category(char **category_elements)
{
	FREE_NULL_TERM_ARRAY(category_elements);
}


/**
  @return An array of malloc pointers that has all the elements of the array in file.
 	  The returned value must be freed using the free_month_spends function.
*/
extern char **get_month_spends(void);

// Free's te elements of the month spends.
static inline void free_month_spends(char **month_spends_elements)
{
	FREE_NULL_TERM_ARRAY(month_spends_elements);
}


#endif
