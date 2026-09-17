#include <stdio.h>
#include <string.h>

/* ============================================================================
   TASK A & B: NAMED CONSTANTS & BINDING TIME DEMONSTRATION
   - Tariff parameters bound at compile time / load time.
   ============================================================================ */

const int BAND1_LIMIT = 10;
const int BAND2_LIMIT = 20;

const double RATE_BAND1 = 25.0;
const double RATE_BAND2 = 35.0;
const double RATE_BAND3 = 50.0;

const double FIXED_CHARGE = 100.0;

const int MAX_CUSTOMERS = 100;

/* ============================================================================
   DATA MODELS
   ============================================================================ */

typedef struct {
    char name[50];
    int previousReading;
    int currentReading;
} Customer;

typedef struct {
    int unitsConsumed;
    double bandCharge;
    double fixedCharge;
    double totalBill;
} Bill;

/* ============================================================================
   TASK A & D: BILLING ENGINE WITH MINIMIZED BLOCK SCOPE
   ============================================================================ */

Bill generateBill(Customer c)
{
    Bill b;
    b.unitsConsumed = c.currentReading - c.previousReading;

    /* ------------------------------------------------------------------------
       TASK D: Block-local 'bandCharge' scoped strictly within each branch
       ------------------------------------------------------------------------ */
    if (b.unitsConsumed <= BAND1_LIMIT)
    {
        double bandCharge = b.unitsConsumed * RATE_BAND1;
        b.bandCharge = bandCharge;
    }
    else if (b.unitsConsumed <= (BAND1_LIMIT + BAND2_LIMIT))
    {
        double bandCharge = (BAND1_LIMIT * RATE_BAND1)
            + ((b.unitsConsumed - BAND1_LIMIT) * RATE_BAND2);
        b.bandCharge = bandCharge;
    }
    else
    {
        double bandCharge = (BAND1_LIMIT * RATE_BAND1)
            + (BAND2_LIMIT * RATE_BAND2)
            + ((b.unitsConsumed - BAND1_LIMIT - BAND2_LIMIT) * RATE_BAND3);
        b.bandCharge = bandCharge;
    }

    b.fixedCharge = FIXED_CHARGE;

    /* ------------------------------------------------------------------------
       TASK C: L-value / R-value Assignment
       b.totalBill (L-value: memory location) 
       = b.bandCharge + b.fixedCharge (R-value: computed value)
       ------------------------------------------------------------------------ */
    b.totalBill = b.bandCharge + b.fixedCharge;

    return b;
}

/* ============================================================================
   TASK D: STATIC COUNTER DEMONSTRATION
   - Static local variable: Allocated at load time; persists across calls.
   ============================================================================ */

int countGeneratedBills(void)
{
    static int billsGenerated = 0;
    billsGenerated++;
    return billsGenerated;
}

/* ============================================================================
   MAIN EXECUTION WORKFLOW
   ============================================================================ */

int main(void)
{
    Customer customers[MAX_CUSTOMERS];
    int numberOfCustomers;
    int i;

    int totalUnits = 0;
    int invalidRecords = 0;
    int highestConsumption = 0;
    double totalRevenue = 0.0;

    printf("Enter number of customers: ");
    if (scanf("%d", &numberOfCustomers) != 1) return 1;

    /* Rule: Minimum of 6 customers required */
    if (numberOfCustomers < 6 || numberOfCustomers > MAX_CUSTOMERS)
    {
        printf("Invalid number of customers. Minimum 6 required.\n");
        return 1;
    }

    for (i = 0; i < numberOfCustomers; i++)
    {
        printf("\n====================================\n");
        printf("Customer %d\n", i + 1);
        printf("====================================\n");

        printf("Enter customer name: ");
        scanf(" %[^\n]", customers[i].name);

        printf("Enter previous meter reading: ");
        scanf("%d", &customers[i].previousReading);

        printf("Enter current meter reading: ");
        scanf("%d", &customers[i].currentReading);
    }

    for (i = 0; i < numberOfCustomers; i++)
    {
        /* Input Validation: currentReading >= previousReading */
        if (customers[i].previousReading < 0 ||
            customers[i].currentReading < 0 ||
            customers[i].currentReading < customers[i].previousReading)
        {
            printf("\n------------------------------------\n");
            printf("INVALID RECORD REJECTED\n");
            printf("Customer: %s\n", customers[i].name);
            printf("Previous reading: %d | Current reading: %d\n", 
                   customers[i].previousReading, customers[i].currentReading);
            printf("------------------------------------\n");

            invalidRecords++;
            continue;
        }

        Bill currentBill = generateBill(customers[i]);
        int billNumber = countGeneratedBills();

        totalUnits += currentBill.unitsConsumed;
        totalRevenue += currentBill.totalBill;

        if (currentBill.unitsConsumed > highestConsumption)
        {
            highestConsumption = currentBill.unitsConsumed;
        }

        /* Print Customer Bill */
        printf("\n====================================\n");
        printf("            WATER BILL              \n");
        printf("====================================\n");
        printf("Bill number     : %d\n", billNumber);
        printf("Customer        : %s\n", customers[i].name);
        printf("Previous reading: %d\n", customers[i].previousReading);
        printf("Current reading : %d\n", customers[i].currentReading);
        printf("Units consumed  : %d\n", currentBill.unitsConsumed);
        printf("Band charge     : KES %.2f\n", currentBill.bandCharge);
        printf("Fixed charge    : KES %.2f\n", currentBill.fixedCharge);
        printf("TOTAL BILL      : KES %.2f\n", currentBill.totalBill);
        printf("====================================\n");
    }

    /* Output Summary */
    printf("\n\n====================================\n");
    printf("           FINAL SUMMARY            \n");
    printf("====================================\n");
    printf("Total customers processed: %d\n", numberOfCustomers);
    printf("Total valid units        : %d\n", totalUnits);
    printf("Total revenue            : KES %.2f\n", totalRevenue);
    printf("Highest consumption      : %d units\n", highestConsumption);
    printf("Invalid records rejected : %d\n", invalidRecords);
    printf("====================================\n");

    return 0;
}