/* FILE: P5.c
 * NAME: Elijah T.he Rose
 * BLID: elirose
 * DATE: 12.16.2018 
 * DESC: Interactive integral calculator. Utilizing functions, build a command line utility that will 
 * calculate various numerical methods using input from a file and provide 
 * output via another file.
 */

/*===========================================================================================
 _____ __   _ _____ _______ _____ _______        _____ ______ _______
   |   | \  |   |      |      |   |_____| |        |    ____/ |______
 __|__ |  \_| __|__    |    __|__ |     | |_____ __|__ /_____ |______
===========================================================================================*/


    //INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>


    //DEFINES
    #define MAX_STRLEN 30
    #define MAX_ARRLEN 200


    //FUNCTION DECLARATIONS
    double numerical_integration_rectangle(char iFilename[], char oFilename[]);
    double numerical_integration_trapezoidal(char iFilename[], char oFilename[]);

    int fileRead(char iFilename[], double xArr[], double yArr[]);
    int fileExport(  char oFilename[], char method[], int segments, double area, 
        double x_min, double x_max, double x_mean, double x_delta_min, double x_delta_max, 
        double y_min, double y_max, double y_mean, double y_delta_min, double y_delta_max);

    double arrMin(double iArr[], int count);
    double arrMax(double iArr[], int count);
    double arrMean(double iArr[], int count);
    double arrDifferential(double iArr[], double dArr[], int count);

    int help(void);
//===========================================================================================










/*===========================================================================================
_______ _______ _____ __   _
|  |  | |_____|   |   | \  |
|  |  | |     | __|__ |  \_|
===========================================================================================*/
int main(int argc, char const *argv[])
{
    int i;
    int Result = 0;

    printf("Number of Arguments: %i\n", argc); 
    printf("Value of first Arguments: %s\n", argv[0]); 
    printf("Value of all Arguments:\n");
    for (i = 0; i < argc; i++) {printf("\t%i: %s\n", i, argv[i]);}
            
    if (argc < 2) {help();} 
    else { 



        /*___________________________________________________________________________________
        _  _ ____ _    ___  
        |__| |___ |    |__] 
        |  | |___ |___ |        
        ___________________________________________________________________________________*/
        if ( !strcmpi(argv[1], "/h") || !strcmpi(argv[1], "/help") ) {
            printf("  Help Mode\n");
            printf("================\n");
            /*------------------------------------------------------------------------------
            ____ ____ ____ ___ ____ __ _ ____ _  _ _    ____ ____
            |--< |=== |___  |  |--| | \| |__, |__| |___ |--| |--<
            ------------------------------------------------------------------------------*/
            //RECTANGULAR_HELP
            if ( !strcmpi(argv[2], "/r") || !strcmpi(argv[2], "/rectangle") ) {
                printf("\nUses left-end rectangle approximation method to approximate the area of\n\
                  the given dataset, where the first column represents x, the second column y.\n");
                printf("\nRemember to include the file extension, .csv and .txt!\n");
                Result = 1;
            }
            /*------------------------------------------------------------------------------
           ___ ____ ____ ___  ____ ___  ____ _ ___  ____ _   
            |  |--< |--| |--' |===  /__ [__] | |__> |--| |___
            ------------------------------------------------------------------------------*/
            else if ( !strcmpi(argv[2], "/t") || !strcmpi(argv[2], "/trapezoid") ) {
                printf("Uses trapezoidal approximation method to approximate the area of\n\
                  the given dataset, where the first column represents x, the second column y.\n");
                printf("\nRemember to include the file extension, .csv (input) and .txt (input or output)! \n");
                Result = 1;
            }
            /*------------------------------------------------------------------------------
            ____ _ _ ____ _  _ ___  _    ____ ____
            |=== _X_ |--| |\/| |--' |___ |=== ====
            ------------------------------------------------------------------------------*/
            else if( !strcmpi(argv[2], "/ex") || !strcmpi(argv[2], "/examples") ) {
                printf("Examples:\n");
                printf("    P5.exe /p /r input_01.csv output_01.txt\n");    
                printf("    P5.exe /i /t < filenameInputs.txt\n");  
                Result = 1;
            } else {help(); printf("\nHelp explicitly called.");}
        }//__________________________________________________________________________________



        /*___________________________________________________________________________________
        _ _  _ ___ ____ ____ ____ ____ ___ _ _  _ ____ 
        | |\ |  |  |___ |__/ |__| |     |  | |  | |___ 
        | | \|  |  |___ |  \ |  | |___  |  |  \/  |___ 
        ___________________________________________________________________________________*/ 
        else if ( !strcmpi( argv[1], "/i" ) || !strcmpi( argv[1], "/interactive" ) ) {
            printf("Interactive Mode\n");
            printf("================\n");
            /*------------------------------------------------------------------------------
            ____ ____ ____ ___ ____ __ _ ____ _  _ _    ____ ____
            |--< |=== |___  |  |--| | \| |__, |__| |___ |--| |--<
            ------------------------------------------------------------------------------*/
             if ( !strcmpi(argv[2], "/r") || !strcmpi(argv[2], "/rectangle") ) {
                char iFilename[MAX_STRLEN];
                char oFilename[MAX_STRLEN];
                printf("\nInsert input filename: ");
                    scanf("%s", iFilename);
                printf("\nInsert output filename: ");
                    scanf("%s", oFilename);
                numerical_integration_rectangle(iFilename, oFilename);
                Result = 1;
            }
           /*------------------------------------------------------------------------------
           ___ ____ ____ ___  ____ ___  ____ _ ___  ____ _   
            |  |--< |--| |--' |===  /__ [__] | |__> |--| |___
            ------------------------------------------------------------------------------*/
            else if ( !strcmpi(argv[2], "/t") || !strcmpi(argv[2], "/trapezoidal") || !strcmpi(argv[2], "/trapezoid") ) {
                char iFilename[MAX_STRLEN];
                char oFilename[MAX_STRLEN];
                printf("\nInsert input filename: ");
                    scanf("%s", iFilename);
                printf("\nInsert output filename: ");
                    scanf("%s", oFilename);
                numerical_integration_trapezoidal(iFilename, oFilename);
                Result = 1;
            } else {help(); printf("\nERR_03: Third input argument not recognized.(i)");} 
        }//__________________________________________________________________________________
        


        /*___________________________________________________________________________________
        ___  ____ ____ ____ _  _ ____ ___ ____ ____ 
        |__] |__| |__/ |__| |\/| |___  |  |___ |__/ 
        |    |  | |  \ |  | |  | |___  |  |___ |  \ 
        ___________________________________________________________________________________*/
        else if ( !strcmpi(argv[1], "/p") || !strcmpi(argv[1], "/parameter") ) {
            printf(" Parameter Mode\n");
            printf("================\n");
            if (argc < 5) {printf("Not enough parameters, check your input."); help();}
            else if (argc > 5) {printf("Too many parameters, check your input."); help();}
           /*------------------------------------------------------------------------------
            ____ ____ ____ ___ ____ __ _ ____ _  _ _    ____ ____
            |--< |=== |___  |  |--| | \| |__, |__| |___ |--| |--<
            ------------------------------------------------------------------------------*/
             else if ( !strcmpi(argv[2], "/r") || !strcmpi(argv[2], "/rectangle") ) {
                char iFilename[MAX_STRLEN];
                char oFilename[MAX_STRLEN];
                strcpy(iFilename, argv[3]);
                strcpy(oFilename, argv[4]);
                numerical_integration_rectangle(iFilename, oFilename);
                Result = 1;
            }
           /*------------------------------------------------------------------------------
           ___ ____ ____ ___  ____ ___  ____ _ ___  ____ _   
            |  |--< |--| |--' |===  /__ [__] | |__> |--| |___
            ------------------------------------------------------------------------------*/
            else if ( !strcmpi(argv[2], "/t") || !strcmpi(argv[2], "/trapezoid") || !strcmpi(argv[2], "/trapezoidal")) {
                char iFilename[MAX_STRLEN];
                char oFilename[MAX_STRLEN];
                strcpy(iFilename, argv[3]);
                strcpy(oFilename, argv[4]);
                numerical_integration_trapezoidal(iFilename, oFilename);
                Result = 1;
            } else {help();printf("\nThird input argument not recognized.(p)");}   
        }//__________________________________________________________________________________
        else { help(); printf("Second input argument not recognized.\n");}
    } return (Result);
}//==========================================================================================










/*===========================================================================================
            _______ _     _ _     _ _____        _____ _______  ______ __   __
            |_____| |     |  \___/    |   |        |   |_____| |_____/   \_/  
            |     | |_____| _/   \_ __|__ |_____ __|__ |     | |    \_    |   
===========================================================================================*/



    /*___________________________________________________________________________________
    ____ ____ ____ ___ ____ _  _ ____ _    ____ 
    |__/ |___ |     |  |__| |\ | | __ |    |___ 
    |  \ |___ |___  |  |  | | \| |__] |___ |___ 
    ___________________________________________________________________________________*/
    double numerical_integration_rectangle(char iFilename[], char oFilename[])  {
        int i = 0;
        double xArr[MAX_ARRLEN]; double yArr[MAX_ARRLEN]; 
            int count = fileRead(iFilename, xArr, yArr);
        double dxArr[MAX_ARRLEN]; 
            arrDifferential(xArr, dxArr, count);
        double dyArr[MAX_ARRLEN];
            arrDifferential(yArr, dyArr, count);
        
        char method[] = "rectangle";
        int segments = count-1;
        double area = 0; while(i<segments) {area += dxArr[i]*yArr[i];i++;} /*left-hand rectanlge*/
        double x_min = arrMin(xArr, count);
        double x_max = arrMax(xArr, count);
        double x_mean = arrMean(xArr, count);
        double x_delta_min = arrMin(dxArr, count);
        double x_delta_max = arrMax(dxArr, count);
        double y_min = arrMin(yArr, count);
        double y_max = arrMax(yArr, count);
        double y_mean = arrMean(yArr, count);
        double y_delta_min = arrMin(dyArr, count);
        double y_delta_max = arrMax(dyArr, count);

        fileExport(oFilename, method, segments, area, 
        x_min, x_max, x_mean, x_delta_min, x_delta_max,
        y_min, y_max, y_mean, y_delta_min, y_delta_max);
        
        return(area);
    }//__________________________________________________________________________________
    


    /*___________________________________________________________________________________
    ___ ____ ____ ___  ____ ___  ____ _ ___  
     |  |__/ |__| |__] |___   /  |  | | |  \ 
     |  |  \ |  | |    |___  /__ |__| | |__/ 
    ___________________________________________________________________________________*/
    double numerical_integration_trapezoidal(char iFilename[], char oFilename[]) {
        int i = 0;
        double xArr[MAX_ARRLEN]; double yArr[MAX_ARRLEN]; 
            int count = fileRead(iFilename, xArr, yArr);
        double dxArr[MAX_ARRLEN]; 
            arrDifferential(xArr, dxArr, count);
        double dyArr[MAX_ARRLEN];
            arrDifferential(yArr, dyArr, count);
        
        char method[] = "trapezoidal";
        int segments = count-1;
        double area = 0; while(i<segments) {area += dxArr[i]*(yArr[i]+yArr[i+1])*0.5;i++;}
        double x_min = arrMin(xArr, count);
        double x_max = arrMax(xArr, count);
        double x_mean = arrMean(xArr, count);
        double x_delta_min = arrMin(dxArr, count);
        double x_delta_max = arrMax(dxArr, count);
        double y_min = arrMin(yArr, count);
        double y_max = arrMax(yArr, count);
        double y_mean = arrMean(yArr, count);
        double y_delta_min = arrMin(dyArr, count);
        double y_delta_max = arrMax(dyArr, count);

        fileExport(oFilename, method, segments, area, 
        x_min, x_max, x_mean, x_delta_min, x_delta_max,
        y_min, y_max, y_mean, y_delta_min, y_delta_max);
        
        return(area);
    }//__________________________________________________________________________________
   


    /*___________________________________________________________________________________
    _ _  _ ___  ____ ____ ___ 
    | |\/| |__] |  | |__/  |  
    | |  | |    |__| |  \  | 
    ___________________________________________________________________________________*/
    int fileRead( char iFilename[], double xArr[], double yArr[]) { 
        FILE *iFile;
        int count = 0;
        double xChunk;
        double yChunk;
        
        iFile = fopen(iFilename, "r");
        if (iFile != NULL) {
            while (fscanf(iFile, "%lf,%lf\n", &xChunk, &yChunk) == 2) {
                xArr[count] = xChunk;
                yArr[count] = yChunk;
                count++;
            }
        } fclose(iFile);

        return( count );
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    ____ _  _ ___  ____ ____ ___ 
    |___  \/  |__] |  | |__/  |  
    |___ _/\_ |    |__| |  \  |  
    ___________________________________________________________________________________*/
        int fileExport(  char oFilename[], char method[], int segments, double area, 
        double x_min, double x_max, double x_mean, double x_delta_min, double x_delta_max, 
        double y_min, double y_max, double y_mean, double y_delta_min, double y_delta_max)
        { 
            FILE* oFile;
            oFile = fopen(oFilename, "w");
            if (oFile != NULL) {
                fprintf(oFile, "  DESCRIPTION                  VALUE\n");
                fprintf(oFile, "========================================\n");
                fprintf(oFile, "  Method                       %s   \n", method);
                fprintf(oFile, "  Segments                     %d   \n", segments);
                fprintf(oFile, "  Area                         %.2lf\n", area);
                fprintf(oFile, "  x_min                        %.2lf\n", x_min);
                fprintf(oFile, "  x_max                        %.2lf\n", x_max);
                fprintf(oFile, "  x_mean                       %.2lf\n", x_mean);
                fprintf(oFile, "  x_delta_min                  %.2lf\n", x_delta_min);
                fprintf(oFile, "  x_delta_max                  %.2lf\n", x_delta_max);
                fprintf(oFile, "  y_min                        %.2lf\n", y_min);
                fprintf(oFile, "  y_max                        %.2lf\n", y_max);
                fprintf(oFile, "  y_mean                       %.2lf\n", y_mean);
                fprintf(oFile, "  y_delta_min                  %.2lf\n", y_delta_min);
                fprintf(oFile, "  y_delta_max                  %.2lf\n", y_delta_max);
                fprintf(oFile, "========================================\n\n");
            } fclose(oFile);
            return(0);
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    _  _ _ _  _ _ _  _ _  _ _  _ 
    |\/| | |\ | | |\/| |  | |\/| 
    |  | | | \| | |  | |__| |  |       
    ___________________________________________________________________________________*/
    double arrMin(double iArr[], int count) {
        int i = 0;
        double min = iArr[0];
        while(i<count) {
            if(iArr[i] < min) {min = iArr[i];} 
            i++;}
        return(min);
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    _  _ ____ _  _ _ _  _ _  _ _  _ 
    |\/| |__|  \/  | |\/| |  | |\/| 
    |  | |  | _/\_ | |  | |__| |  | 
    ___________________________________________________________________________________*/
    double arrMax(double iArr[], int count) {
        int i = 0;
        double max = iArr[0];
        while(i<count) {
            if(iArr[i] > max) {max = iArr[i];} 
            i++;}
        return(max);
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    _  _ ____ ____ _  _ 
    |\/| |___ |__| |\ | 
    |  | |___ |  | | \| 
    ___________________________________________________________________________________*/
    double arrMean(double iArr[], int count) {
        int i = 0;
        double sum = 0;
        while(i<count) {
            sum += iArr[i];
            i++;}
        return(sum/count);
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    ___  _ ____ ____ ____ ____ ____ _  _ ___ _ ____ _    
    |  \ | |___ |___ |___ |__/ |___ |\ |  |  | |__| |    
    |__/ | |    |    |___ |  \ |___ | \|  |  | |  | |___ 
    ___________________________________________________________________________________*/
    double arrDifferential(double iArr[], double dArr[], int count) {
        int i = 0;
        while( i<(count-1) ) {
            dArr[i] = iArr[i+1] - iArr[i]; i++;}
        return(count - 1);
    }//__________________________________________________________________________________



    /*___________________________________________________________________________________
    _  _ ____ _    ___  
    |__| |___ |    |__] 
    |  | |___ |___ |        
    ___________________________________________________________________________________*/
    int help(void) {
        printf("========================================\n");
        printf("FILE: P5.exe\n");
        printf("Vers: 1.0.0 10/05/2018 ETR\n");
        printf("Desc: Integral Calculator File I/O\n");
        printf("_________________________________________\n");
        printf("Usage:\n");
        printf("    /i - Interactive mode\n");
        printf("        /r - rectangular approximation\n");
        printf("        /t - trapezoidal approximation\n");
        printf("    /p - Parameter mode\n");
        printf("        /r - rectangular approximation\n");
        printf("            <inputFilename>\n");
        printf("            <outputFilename>\n");
        printf("        /t - trapezoidal approximation\n");
        printf("            <inputFilename>\n");
        printf("            <outputFilename>\n");
        printf("    /h - Help\n");
        printf("        /r - rectangular approximation\n");
        printf("        /t - trapezoidal approximation\n"); 
        printf("        /ex - examples\n");
        printf("    NOTE: INCLUDE FILE EXTENSION IN NAME\n");
        printf("========================================\n");
        return (EXIT_SUCCESS);
    }//__________________________________________________________________________________
//===========================================================================================










/*===========================================================================================
 _____ __   _ _______ _______  ______ _     _ _______ _______ _____  _____  __   _ _______
   |   | \  | |______    |    |_____/ |     | |          |      |   |     | | \  | |______
 __|__ |  \_| ______|    |    |    \_ |_____| |_____     |    __|__ |_____| |  \_| ______|
                                                                                          
===========================================================================================*/
/* Problem{01}: Utilizing the numerical_integration_v1 example from 
 * Class_09_Driver.c and what we have learned from P3, develop an algorithm 
 * to process command line switches to handle the following requirements.
 * 
 * From the command window, the user should be able to run the program in 
 * several tier one modes:
 *  Help mode (implicit and explicit)
 *  Interactive mode - scanf
 *  Parameter mode - parsed from argv[n]
 * For both Interactive and Parameter mode, the user should be able to choose 
 * from each of the tier two modes:
 *  /rectangle - implements the rectangle method using the midpoint
 *  /trapezoidal - implements the trapezoidal method
 * The third parameter (immediately following the summation method) should be 
 * the filename of the two column .csv file that contains your input data.
 * The fourth parameter should be the filename of the two column .txt file that 
 * contains your output data.
 * 
 * If incorrect or insufficient arguments are provided, help must be displayed. 
 * 
 *  * Functions:
 *  double numerical_integration_rectangle(char *input_filename, *output_filename) 
 *  double numerical_integration_trapezoidal(char *input_filename, *output_filename )
 * 
 * Input sample (each on its own line):
 *  Enter the input filename:
 *  Enter the output filename:
 * 
 * Output sample (in output text file):
 * Description                  Value
 * =============================================================================
 * Method                       rectangle
 * Segments                     100
 * Area                         0.67
 * x_min                        0.00
 * x_max                        1.00
 * x_mean                       0.50
 * x_delta_min                  0.01
 * x_delta_max                  0.01
 * y_min                        0.00
 * y_max                        1.00
 * y_mean                       0.67
 * y_delta_min                  0.00
 * y_delta_max                  0.02
 * 
 * Output sample (in output .csv file): 
 *      See rectangle_temp.csv
 * 
 * 
 * Deliverables: 
 *  p5.c
 *  p5.exe
 *  rectangle_summary.txt
 *  rectangle_temp.csv
 *  trapezoidal_summary.txt
 *  trapezoidal_temp.csv 
 */
//===========================================================================================