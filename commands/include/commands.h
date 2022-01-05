#ifndef TERMINAL_BUDGET_TRACKER_COMMANDS_H
#define TERMINAL_BUDGET_TRACKER_COMMANDS_H


void available_amount_command(void);

void available_category_amount_command(const char *category);

void set_budget_command(const char *budget);

void change_budget_command(const char *budget);

void add_category_command(const char *catergory, const char *budget);

void change_category_budget_command(const char *catergory, const char *budget);

void delete_category_command(const char *category);

void show_statistics_command(void);

void show_prefered_daily_spend_command(void);

void show_future_spend_command(void);

void show_categories_command(void);

void show_category_command(const char *category);

void show_merchant_command(const char *merchant);

void show_merchants_command(void);

void show_all_expenses_command(const char *type, const char *name);

void add_expenses_command(const char *merchant, char *amount,
				  		  const char *date);

void associate_merchant_command(const char *merchant, const char *category);

void help_command(void);

#endif

