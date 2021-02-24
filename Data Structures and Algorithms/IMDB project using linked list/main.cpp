/*======================================================================================================
 *          
 * =====================================================================================================
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

//=======================Forward Declaration of Classes===================

////        classes related to director stuff
//
class DirectorData;        //stores information of director
class DirectorNode;        //Node class
class DirectorList;        //Linked List to connect DirectorNode

//
////        classes related to actor list
//
class ActorData;        //stores information of actor
class ActorNode;        //Node class
class ActorList;        //Linked List to connect ActorNode

//
////       classes related to movie list
//
class MovieData;        //stores information of Movie
class MovieNode;        //Node class
class MovieList;        //Linked List to connect MovieNode

////
////        function for upper case converting, helps in search functions
////
//takes string, changes cases t upper case character by character
//big 0 complexity is n
string upper_string(string str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')   //checking for lowercase characters
            str[i] = str[i] - 32;        //converting lowercase to uppercase
    }
    return str;
}

////
////    MovieData class, holding 28 data fields of a single movie which relate to CSV file.
////    used as user defined data type.
////	Pointers for directors and actors are used
////
class MovieData {
public:
    string movieTitle;
    string genres;
    unsigned short int titleYear;
    float imdbScore;
    DirectorData *director;        //stores pointer for director
    unsigned short int numCriticForReviews;
    unsigned short int duration;
    ActorData *actors[3];        //stores 3 pointers which point to ActorData
    unsigned int gross;
    unsigned int numVotedUsers;
    unsigned int castTotalFacebookLikes;
    unsigned short int faceNumberInPoster;
    string plotKeywords;
    string movieImdbLink;
    unsigned short int numUserForReviews;
    string language;
    string country;
    string contentRating;
    double budget;
    float aspectRatio;
    unsigned int movieFacebookLikes;
    string color;
};

////
////    movie node class to store movie data and next ptr field
////
class MovieNode {
public:
    MovieData *pmData;        //points to data of Movie
    MovieNode *next;        //points to next node
};

////
////    class to implement movies linked list
////
class MovieList {
public:
    //pointers to maintion movie list
    MovieNode *start;
    MovieNode *last;
    MovieNode *loc;
    MovieNode *ploc;

    //some checks to be used in functionn
    bool valFound;
    bool printAscendingYears;

    //constructor for movie list and Initializing variables
    MovieList() {

        start = NULL;
        valFound = false;
        printAscendingYears = true;
    }

    //function to check, if movie list is empty or not
    bool MovieListIsEmpty() {

        return start == NULL;
    }

    //creates a new node and inserts the node in the end of the movie linked list
    void InsertAtEndm(MovieData *mov) {

        MovieNode *newNode = new MovieNode();
        newNode->pmData = mov;
        if (MovieListIsEmpty()) {                //executes if Movie List is empty
            start = newNode;                //updating where nodes point to

        } else {
            last->next = newNode;        //executes if more than one value present in list
        }
        last = newNode;
    }

    //creates a new node and inserts the node in the front(start) of the linked list
    void InsertAtFrontm(MovieData *mov) {
        MovieNode *newNode = new MovieNode();
        newNode->pmData = mov;
        if (MovieListIsEmpty()) {
            start = newNode;
            last = newNode;                    //newnode is both the first and last value of list
        } else {
            newNode->next = start;          //executes if more than one value present in list
            start = newNode;
        }
    }

    //searches the logical position(front, end or somewhere in between) of the movie obj in list to be inserted
    void SearchMovie(MovieData *obj) {

        ploc = NULL;
        loc = start;
        if (MovieListIsEmpty()) {
            return;
        }
        while (loc != NULL && loc->pmData->movieTitle < obj->movieTitle) {         //loop runs till value is found
            ploc = loc;
            loc = loc->next;
        }
        if (loc != NULL && loc->pmData->movieTitle != obj->movieTitle) {
            loc = NULL;    //as value is not found so set loc equal to null.
        }
        //end of search function.
    }

    //calls the search function and inserts the movie in the logical position by comparing loc and ploc
    //movieData can be inserted at front, end, or somewhere in between of MovieList depending on value of loc
    void InsertSortedMovies(MovieData *md) {

        SearchMovie(md);                //searches logical position of MovieData
        if (loc != NULL) {                //if currLoc is not null, means value already exists in list
            return;
        } else {                            // if currLoc is null, then..
            if (ploc ==
                NULL) {            //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
                InsertAtFrontm(md);
            } else {                        //if currLoc is NULL and predLoc is not NULL, then..
                if (ploc == last) {        //if predLoc has last node address, value will be inserted to the end
                    InsertAtEndm(md);
                } else {                    //if somewhere in between list and logical position is found

                    MovieNode *newNode = new MovieNode();
                    newNode->pmData = md;
                    newNode->next = ploc->next;            //next pointers updated
                    ploc->next = newNode;
                }
            }
        }
    }

    // searches loc for rating, will be used for list creation rating wise
    //returns loc which is required later on
    void SearchMovieRating(float score) {
        ploc = NULL;
        loc = start;

        if (MovieListIsEmpty()) {
            cout << " movie List is Empty!" << endl;               //exits function if list is empty
            return;
        }

        while (loc != NULL && (loc->pmData->imdbScore < score ||
                               loc->pmData->imdbScore == score)) {         //loop runs till value is found
            ploc = loc;
            loc = loc->next;
        }

        if (loc != NULL && loc->pmData->imdbScore != score) {
            loc = NULL;    //as value is not found so set loc equal to null.
        } //end of search function.

    }


    // uses SearchMovieRating() function and inserts movie obj in list rating wise
    // maintains sorted rating wise list
    void InsertSortedMoviesRating(MovieData *md) {
        SearchMovieRating(md->imdbScore);
        if (loc != NULL) { //if currLoc is not null, means value already exists in list

            //cout<<value<<" already exists hence khali wali"<<endl;
            return;
        } else { // if currLoc is null, then..

            if (ploc == NULL) { //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
                InsertAtFrontm(md);
            } else { //if currLoc is NULL and predLoc is not NULL, then..
                if (ploc == last) { //if predLoc has last node address, value will be inserted to the end
                    InsertAtEndm(md);
                } else { //if somewhere in between list and logical position is found
                    MovieNode *newNode = new MovieNode();
                    newNode->pmData = md;
                    newNode->next = ploc->next;
                    ploc->next = newNode;
                }
            }
        }
    }


    // to search year wise and return loc
    void SearchMovieYear(int year) {

        ploc = NULL;
        loc = start;
        if (MovieListIsEmpty()) {
            cout << "Movie List is Empty!" << endl;            //exits function if list is empty
            return;
        }
        while (loc != NULL &&
               (loc->pmData->titleYear < year || loc->pmData->titleYear == year)) {   //loop runs till value is found
            ploc = loc;
            loc = loc->next;
        }
        if (loc != NULL && loc->pmData->titleYear != year) {
            loc = NULL;                                            //as value is not found so set loc equal to null.
        }
        //end of search function.
    }

    // uses search year function to search logical position, and inserts movie year wise, chronologically in maintained list
    void InsertSortedMoviesYear(MovieData *md) {

        SearchMovieYear(
                md->titleYear);         //Title Year of Movie is compared to nodes present in movieList to find the node's logical position
        if (loc != NULL) {                     //if currLoc is not null, means value already exists in list
            return;
        } else {                                 // if currLoc is null, then..
            if (ploc ==
                NULL) {                 //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
                InsertAtFrontm(md);
            } else {                             //if currLoc is NULL and predLoc is not NULL, then..
                if (ploc == last) {             //if predLoc has last node address, value will be inserted to the end
                    InsertAtEndm(md);
                } else {                         //if somewhere in between list and logical position is found
                    MovieNode *newNode = new MovieNode();
                    newNode->pmData = md;
                    newNode->next = ploc->next;
                    ploc->next = newNode;
                }
            }
        }
    }

///=============Forward Declared Functions==============

    //prints all the movies in the movies list
    void PrintMovieList();

    //will be used for function 1
    void PrintMovieListInDetail();

    //print the actors of the given movie
    void PrintActorsOfMovie(string name);

    // print coactors of certain actor
    void PrintCoActorMovieList(string ss);

    //for searching co actors of co actors
    void SearchCoActorCoActorMovieListlevel2(string ss, string sx);

    // for printing co actors of co actors
    void PrintCoActorssF4(string ss, string sx);

    // for printing movies rating wise
    void PrintMoviesRatingWise();

    //for printing movies year wise
    void PrintMoviesYearWise(bool printInAscendingYears);

    // printi in decending year
    void PrintMoviesInDescendingYear(MovieNode *mn);

    // print details of movie
    void PrintDetailsOfMovie(string name);

    // print directors of certain genre
    void PrintDirectorsOfGenre(string genre);

    //print movies of given genre
    void PrintMoviesOfGenre(string genre);

    //prints movies of given year
    void PrintMoviesOfYear(int year);

};


//
////  for actor node storing actor data and having next ptr field
//
class ActorNode {
public:
    ActorData *paData;        //points to ActorData
    ActorNode *next;        //points to next Actor Node
};

//
////to create a node for director information and next ptr field
//
class DirectorNode {
public:
    DirectorData *pData;    //points to DirectorData
    DirectorNode *next;        //points to next Director Node
};

//
//// datatype to hold director name and likes
//
class DirectorData {
public:
    string directorName;                        //to store director name
    unsigned short int directorFacebookLikes;   //to store director likes

    //maintains the list of movies directed by the certain director
    MovieList *moviesDirected = new MovieList();
};

//
//// maintaining director list
//
class DirectorList {
public:
    DirectorNode *start;
    DirectorNode *last;
    DirectorNode *loc;
    DirectorNode *ploc;

    //constructor
    DirectorList() {

        start = NULL;
        last = NULL;
        loc = NULL;
        ploc = NULL;
    }

    //to check if list is empty
    bool DirectorListIsEmpty() {

        return start == NULL;
    }

    //inserting at end of maintained list
    void InsertAtEndd(DirectorData *dd) {

        DirectorNode *newNode = new DirectorNode();
        newNode->pData = dd;
        if (DirectorListIsEmpty()) {
            start = newNode;                //executes if list is empty
        } else {
            last->next = newNode;            //executes if nodes already exist in list
        }
        last = newNode;
    }

    // insert at front of maintained list
    void InsertAtFrontd(DirectorData *dd) {

        DirectorNode *newNode = new DirectorNode();
        newNode->pData = dd;
        if (DirectorListIsEmpty()) {
            start = newNode;
            last = newNode;                    //newnode is both the first and last value of list
        } else {
            newNode->next = start;          //executes if more than one value present in list
            start = newNode;
        }
    }

    //search director logical position for inserting in list, alphabetically, returns loc
    void SearchDirector(DirectorData *dd) {

        ploc = NULL;
        loc = start;
        if (DirectorListIsEmpty()) {
            return;
        }
        while (loc != NULL && loc->pData->directorName < dd->directorName) {         //loop runs till value is found
            ploc = loc;
            loc = loc->next;
        }
        if (loc != NULL && loc->pData->directorName != dd->directorName) {
            loc = NULL;                    //as value is not found so set loc equal to null.
        }
        //end of search function.
    }

    //insert the directors sorted in director list
    void InsertSortedDirectors(DirectorData *dd, MovieData *md) {
        SearchDirector(dd);             //DirectorData passed to find its logical position in list
        if (loc != NULL) {             //means value already exists in list
            loc->pData->moviesDirected->InsertAtEndm(md);
            return;
        } else {                        // if currLoc is null, then..
            if (ploc ==
                NULL) {        //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
                InsertAtFrontd(dd);
            } else {                    //if currLoc is NULL and predLoc is not NULL, then..
                if (ploc == last) {   //if predLoc has last node address, value will be inserted to the end
                    InsertAtEndd(dd);
                } else {                 //if somewhere in between list and logical position is found
                    DirectorNode *newNode = new DirectorNode();
                    newNode->pData = dd;
                    newNode->next = ploc->next;        //updating pointers of nodes
                    ploc->next = newNode;
                }
            }
        }
    }

    // traverse through the director list maintained and print contents of each node in director linked list
    // Big 0 time complexity in n
    void PrintDirectorList() {
        DirectorNode *temp; //temp node for traversing
        if (!DirectorListIsEmpty()) {
            int i = 1;
            temp = start;             //initialize the temp
            while (temp != NULL) {     //looping till temp is not null
                cout << " Director Node: " << i << " " << temp->pData->directorName << " got likes: "
                     << temp->pData->directorFacebookLikes << endl; //print Director's name and likes
                temp = temp->next;
                i++;
            }
        } else {
            cout << "List is Empty" << endl;
        }
    }

    //prints the director list and the movies they directed
    // as we already know that we have maintained a list of movies with each director for the movies he/she directed
    //so this function prints all the directors and their movies in order
    // big 0 complexity is N
    void PrintDirectorListAndTheMoviesTheyDirected() {

        cout << "Printing list..." << endl;
        DirectorNode *temp;                //storing current node in temp ptr

        if (!DirectorListIsEmpty()) {
            int i = 1;                    //count variable
            temp = start;                //initialize the temp
            while (temp != NULL) {        //looping till temp is not null

                //print director info
                cout << " Director Node: " << i << " " << temp->pData->directorName << " got likes: "
                     << temp->pData->directorFacebookLikes << ".\n Directed ";

                //print movies list that director directed
                temp->pData->moviesDirected->PrintMovieList();
                cout << endl;
                temp = temp->next;
                i++;
            }
        } else {
            cout << "List is Empty!" << endl;
        }
    }

    // prints movies directed by certain director
    // we pass the name of director, and loop through the directors list
    // if anynode director name matches with string passed, we print the movies he directed from movies dircted list
    // after that we return
    // so Big 0 complexity is N can we iterating in a single go
    void PrintMoviesDirectedBy(string dName) {

        //initialzing variables
        loc = start;
        bool valFound = false;                  //indicated if Director has been found
        string upperName = upper_string(dName); //converts string to uppercase

        while (loc != NULL) {
            if (upper_string(loc->pData->directorName) == upperName) {

                valFound = true;
                cout << endl;
                cout << "Movies Directed By: " << loc->pData->directorName << endl;
                cout << "---------------------------------------------------------" << endl;
                loc->pData->moviesDirected->PrintMovieList();    //function prints movies directed by director
                return;                          //if value found, no need to traverse till end of Director list and function stops
            }
            loc = loc->next;
        }
        if (!valFound) {
            cout << "Director: '" << dName << "' was not found!" << endl;
        }
    }
};

//
////  maintains the actor list
//
class ActorList {
public:
    ActorNode *start;
    ActorNode *last;
    ActorNode *loc;
    ActorNode *ploc;
    bool valFound;


    //constructors
    ActorList() {
        start = NULL;
    }

    //checks if empty
    bool ActorListIsEmpty() {
        valFound = false;
        return start == NULL;
    }

    //inserts at end of list
    void InsertAtEnda(ActorData *ad) {

        ActorNode *newNode = new ActorNode();
        newNode->paData = ad;
        if (ActorListIsEmpty()) {
            start = newNode;                //executes if list is empty
        } else {
            last->next = newNode;            //executes if nodes already exist in list
        }
        last = newNode;
    }

    //inserts at front of list
    void InsertAtFronta(ActorData *ad) {

        ActorNode *newNode = new ActorNode();
        newNode->paData = ad;
        if (ActorListIsEmpty()) {
            start = newNode;
            last = newNode;                    //newnode is both the first and last value of list
        } else {
            newNode->next = start;          //executes if more than one value present in list
            start = newNode;
        }
    }

//================Forward Declaration of Functions================

    //prints the actor list
    void PrintActorList();

    //prints all the actors and the movies they acted in
    void PrintActorListAndMoviesTheyActIn();

    // search the certain actor in list and return position, helps in sorting
    void SearchActor(ActorData *obj);

    //inserts sorted actors based on loc
    void InsertSortedActors(ActorData *ac, MovieData *md, ActorData *coAct1, ActorData *coAct2);

    //void InsertSortedActors(ActorData *ac,MovieData *md);
    void InsertSortedCoActors(ActorData *ac);

    //print the details of actor, and movies he acted in
    void SearchActorDetails(string aName);

    // searches and print coactors
    void PrintCoActorDetails(string aName);

    // prints unique co actors for an actor
    void PrintUniqueCoActors(string aname);

    //searches if 2 inputs are co-actors and if they are then it prints the movies they have acted in
    void AreBothCoActors(string act1, string act2);

    //prints coActors of coActors of an actor
    void SearchCoActorOfCoActor(string aname);
};
//

//crearting Global lists
MovieList ml;
ActorList al;
DirectorList dl;
// for year wise and rating wise lists
MovieList mlYear;
MovieList mlRating;

//// actor data class, maintains actor information
//
class ActorData {
public:
    string actorName;
    unsigned short int actorFacebookLikes;

    //maintains co actors list of the actor
    ActorList *coActors = new ActorList();

    //maintains list of movies this actor acted in
    MovieList *MoviesActedIn = new MovieList();
};

// prints  actors from actorlist
// traverse through the linked list maintained for unique actors and prints em
// big0 complexity is N
//big Omega time complexity is N
void ActorList::PrintActorList() {

    ActorNode *temp;
    if (!ActorListIsEmpty()) {
        cout << "Printing list" << endl;
        int i = 1;                 //count variable
        temp = start->next;         //initialize the temp
        while (temp != NULL) {     //looping till temp is not null
            cout << "Actor Node: " << i << ": " << temp->paData->actorName << "\t\t got likes: "
                 << temp->paData->actorFacebookLikes << endl;  //print actor name and facebook likes
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is empty!" << endl;
    }
}

// traverse through the actors list and for each actor print the movies they acted in
// big 0 complexity is N
// big Omega complexity is N
void ActorList::PrintActorListAndMoviesTheyActIn() {

    cout << "bout to print list.." << endl;
    ActorNode *temp;             //storing current node in temp ptr

    if (!ActorListIsEmpty()) {
        cout << "Printing list" << endl;
        int i = 1;                 //count variable
        temp = start->next;         //initialize the temp
        while (temp != NULL) {     //looping till temp is not null
            cout << "Actor Node: " << i << ": " << temp->paData->actorName << endl;  //print actor name
            temp->paData->MoviesActedIn->PrintMovieList();                    //function prints list of movies the actor has starred in
            cout << endl;
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is Empty" << endl;
    }
}

// function to search position for actor to place in linked list alphabetically, returns loc
void ActorList::SearchActor(ActorData *obj) {

    ploc = NULL;
    loc = start;
    if (ActorListIsEmpty()) {        //function exists if list is empty
        return;
    }
    while (loc != NULL && loc->paData->actorName <
                          obj->actorName) {         //loop runs till value is found. Names of actors are compared
        ploc = loc;
        loc = loc->next;
    }
    if (loc != NULL && loc->paData->actorName != obj->actorName) {
        loc = NULL;                    //as value is not found so set loc equal to null.
    }
    //end of search function.
}

//inserts sorted actors
// inserts each actor in linked list sorted and stores their co actors with them in the maintained co actors linked list
// if actor already exists in actor list, movie is appended to his moviesactedin linked list
// whereas repeating co actors in co actors linked list that was created in ActorData
//big O complexity N^2
//big Omega complexity N^2
void ActorList::InsertSortedActors(ActorData *ac, MovieData *md, ActorData *coAct1, ActorData *coAct2) {

    SearchActor(ac);        //Logicial position of actor is searched

    if (loc != NULL) {
        loc->paData->MoviesActedIn->InsertSortedMoviesYear(md);  //Movie Inserted in List
        loc->paData->coActors->InsertSortedCoActors(coAct1);     //CoActor1 inserted logically in list
        loc->paData->coActors->InsertSortedCoActors(coAct2);     //CoActor2 inserted logically in list
        return;
    } else { // if currLoc is null, then..
        if (ploc ==
            NULL) { //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
            InsertAtFronta(ac);
            ac->coActors->InsertSortedCoActors(coAct1);            //CoActor1 inserted logically in list
            ac->coActors->InsertSortedCoActors(coAct2);            //CoActor2 inserted logically in list

        } else { //if currLoc is NULL and predLoc is not NULL, then..
            if (ploc == last) { //if predLoc has last node address, value will be inserted to the end
                InsertAtEnda(ac);
                ac->coActors->InsertSortedCoActors(coAct1);        //CoActor1 inserted logically in list
                ac->coActors->InsertSortedCoActors(coAct2);        //CoActor2 inserted logically in list
            } else { //if somewhere in between list and logical position is found
                ActorNode *newNode = new ActorNode();
                newNode->paData = ac;
                newNode->next = ploc->next;
                ploc->next = newNode;

                ac->coActors->InsertSortedCoActors(coAct1);        //CoActor1 inserted logically in list
                ac->coActors->InsertSortedCoActors(coAct2);        //CoActor2 inserted logically in list
            }
        }
    }
}

//search actor details
// traverses through the actors linked list, if actor is found, prints the list of movies he acted in
// big 0 complexity is N, best case is if actor is at first position of list
void ActorList::SearchActorDetails(string aName) {

    loc = start;
    string upName = upper_string(aName);  //Uppercase string saved for comparison

    while (loc != NULL) {
        if (upper_string(loc->paData->actorName) == upName) {
            cout << "Actor " << aName << " found \n";
            loc->paData->MoviesActedIn->PrintMovieListInDetail(); //prints detailed information of movies
            return;
        }
        loc = loc->next;
    }
}

// search co actors details1
// traverses through the actor list
// if the actor is found prints his movies and co actors in them movies
// big 0 time complexity is equal to big Omega time complexity, which is = N
void ActorList::PrintCoActorDetails(string aName) {

    loc = start;
    string upName = upper_string(aName);  //Uppercase string saved for comparison

    while (loc != NULL) {
        if (upper_string(loc->paData->actorName) == upName) {
            cout << "Actor " << aName << " found \n";
            loc->paData->MoviesActedIn->PrintCoActorMovieList(aName); //prints information of movies
            return;
        }
        loc = loc->next;
    }
}

// inserts co actors in the co actors linked list alphabetically order
// big 0 time complexity is N
//big omega time complexity is N
void ActorList::InsertSortedCoActors(ActorData *ac) {

    SearchActor(ac);                //searches logical position for new ActorData
    if (loc != NULL) {
        return;
    } else {                            // if currLoc is null, then..
        if (ploc ==
            NULL) {            //if predloc and currLoc both null, means position is found and list is empty so value will be added to front of list
            InsertAtFronta(ac);
        } else {                        //if currLoc is NULL and predLoc is not NULL, then..
            if (ploc == last) {        //if predLoc has last node address, value will be inserted to the end
                InsertAtEnda(ac);
            } else {                    //if somewhere in between list and logical position is found
                ActorNode *newNode = new ActorNode();
                newNode->paData = ac;
                newNode->next = ploc->next;  //changing where pointers point
                ploc->next = newNode;
            }
        }
    }
}


//prints unique coactors for an actor
//user gives actor name as input
//actor name is searched for in Actor List
//if found each member of his coActor list is selected. Both the actor and coActors name is searched in MovieList
//when the names match the movie title is printed for movies in which the actor and co-actor worked in
//Big O time complexity is same as Big Omega time complexity which is: (N*M*O)
//N - ActorList
//M - CoActorList of Actor
//O - MovieList

void ActorList::PrintUniqueCoActors(string name) {

    loc = start;
    bool valFound = false;                    //bool to save if actor has been found or not
    string upperName = upper_string(name);    //upper string name saved

    while (loc != NULL && !valFound) {
        if (upper_string(loc->paData->actorName) == upperName) {  //if actor name found
            valFound = true;
            string act1Name = loc->paData->actorName;               //actor name saved in string for printing later
            ActorNode *tempCoAct = loc->paData->coActors->start;    //current coActor node saved in tempNde
            while (tempCoAct != NULL) {
                cout << endl;
                string act2Name = tempCoAct->paData->actorName;     //coactor name saved in string
                cout << act1Name << " has worked with " << act2Name << " on the following movie(s)" << endl;
                ml.loc = ml.start;
                while (ml.loc != NULL) {                              //movie list traversed till common movies found and then movie name is printed

                    if ((ml.loc->pmData->actors[0]->actorName == act1Name || ml.loc->pmData->actors[1]->actorName == act1Name || ml.loc->pmData->actors[2]->actorName == act1Name)
                        && (ml.loc->pmData->actors[0]->actorName == act2Name || ml.loc->pmData->actors[1]->actorName == act2Name || ml.loc->pmData->actors[2]->actorName == act2Name)) {  // checking to see if names match in actor array of MovieList
                        cout << ml.loc->pmData->movieTitle << endl;
                    }
                    ml.loc = ml.loc->next;                          //moving to next node of MovieList
                }

                tempCoAct = tempCoAct->next;                        //moving to next node of CoActorList

            }
        }

        loc = loc->next;                                            //moving to next node of Actor List
    }
    if (!valFound) {
        cout << "No actor was found with the name \"" << name << "\"" << endl;
    }
}
// funnction to search if the actors are co actors
// takes 2 names as input
// both names entered are compared and the one that comes alphabetically first is searched for ActorList
// to traverse through the actor which is found first in the actor linked list
// if a actor is found early then we traverse thorugh its sub linked list of co actors till second string actor is found
// if both are found then loops through movie list to print their movies
// big 0 complexity is N^2
//best case complexity (N*M)
//Since names of both actors can be anywhere in the list and not necessarily at the end

void ActorList::AreBothCoActors(string act1, string act2) {

    //declaring variables
    string act1Upper = upper_string(act1);     //save uppercase strings
    string act2Upper = upper_string(act2);
    string act1Name;                           //strings created for printing purposes
    string act2Name;
    bool areCoActors = false;                   //bool used as a check
    loc = start;

    if (act1 < act2) {                           //comparing strings || alphabetically smaller string is searched for in Actor list

        while (loc != NULL) {                       //searches for actor1
            if (((upper_string(loc->paData->actorName).find(act1Upper) !=
                  string::npos))) {    //executes if name of actor is found in list

                act1Name = loc->paData->actorName;                //actor name saved in string
                ActorNode *coAct = loc->paData->coActors->start;  //actor node for CoActor
                while (coAct != NULL) {                            //searches for co-actors name

                    if ((upper_string(coAct->paData->actorName).find(act2Upper) !=
                         string::npos)) { //executes if name of co-actor is found in list

                        act2Name = coAct->paData->actorName;    //co actor name saved to string
                        cout << loc->paData->actorName << " and " << coAct->paData->actorName << " are Co-Actors!"
                             << endl;   //printing actor and co actor names
                        areCoActors = true;
                        break;
                    }
                    coAct = coAct->next;    //move to next node
                }
                break;
            }
            loc = loc->next;                //move to next notde
        }
    } else {                                    //executes if stringact2 is alphabetically shorter than act1 - rest of the statement is same as above

        while (loc != NULL) {                //
            if (((upper_string(loc->paData->actorName)).find(act2Upper) != string::npos)) {

                act1Name = loc->paData->actorName;                 //Save name of actor in string
                ActorNode *coAct = loc->paData->coActors->start; //actor node to find coActor
                while (coAct != NULL) {
                    if (((upper_string(coAct->paData->actorName)).find(act1Upper) != string::npos)) {
                        act2Name = coAct->paData->actorName;     //save name of actor in string
                        cout << loc->paData->actorName << " and " << coAct->paData->actorName << " are Co-Actors!"
                             << endl;
                        areCoActors = true;
                        break;
                    }
                    coAct = coAct->next; //move to next node
                }
                break;
            }
            loc = loc->next;            //move to next node
        }
    }
    if (!areCoActors) {
        cout << act1 << " and " << act2 << " are not Co-Actors!" << endl;
    } else {                                                   //executes if both are coactors and searches for movies they worked in together
        cout << "Movies they have acted together in are: " << endl;
        ml.loc = ml.start;
        while (ml.loc != NULL) {                               //traversing through movie list
            if ((ml.loc->pmData->actors[0]->actorName == act1Name || ml.loc->pmData->actors[1]->actorName == act1Name ||
                 ml.loc->pmData->actors[2]->actorName == act1Name)
                &&
                (ml.loc->pmData->actors[0]->actorName == act2Name || ml.loc->pmData->actors[1]->actorName == act2Name ||
                 ml.loc->pmData->actors[2]->actorName ==
                 act2Name)) {   //executes if a movie data object contains names of both actor1 and actor2
                cout << ml.loc->pmData->movieTitle << endl;    //movie name printed
            }
            ml.loc = ml.loc->next;                           //move to next node
        }
    }
}


// searches co actor of co actor
// calls 2 more functions in sub level
// first we traverse through actor list, if main actor found
// then jumps into his movies , from those movies we search for coactor other than main actor
// now in co actors, we search for their co actros by traversing through the co actors list of em
// and print them
// big 0 complexity N^3
//Big Omega complexity (N*M*O)
//Since size of lists vary
void ActorList::SearchCoActorOfCoActor(string aname) {
    loc = start;
    string upName = upper_string(aname);        //uppercase name saved
    while (loc != NULL) {
        if (upper_string(loc->paData->actorName) == upName) {   //name is searched for in ActorList
            cout << " Main Actor is " << aname << " \n";
            loc->paData->MoviesActedIn->SearchCoActorCoActorMovieListlevel2(upName,
                                                                            upName);  //Function call to find coActors
            return;
        }
        loc = loc->next;
    }
}

//
//// parsing functio, fills list and creats em and link em
//

void PopulateStuff(string fileName) {

    ifstream myFile;                //object or file
    myFile.open(fileName);            //name of file passed
    string list[28];                //array created to save fields from CSV file

    string line;
    getline(myFile, line, '\n');


    int i = 0;
    while (myFile.good()) {
        for (int i = 0; i < 28; i++) {        //inserting fields into array

            if (i % 27 == 0 && i != 0) {        //parsing the last column of CSV file
                getline(myFile, line, '\n');    //delimiter changed from \t to \n
                if (!line.empty())
                    list[i] = line;
                else
                    list[i] = "0000";            //NULL fields in CSV replaced by 0000
                continue;
            }

            getline(myFile, line, '\t');

            if (!line.empty())
                list[i] = line;
            else
                list[i] = "0000";

        }

        if (myFile.eof())                       //Parsing stops if end of file has been reached
            break;

        MovieData *tempm = new MovieData();        //New MovieData object stores the fields
        //stoi used to convert strings to int
        //stod used to convert string to double
        tempm->movieTitle = list[0];
        tempm->genres = list[1];
        tempm->titleYear = stoi(list[2]);;
        tempm->imdbScore = stof(list[3]);
//        tempm->directorName=list[4];
//        tempm->directorFacebookLikes=stoi(list[5]);
        tempm->numCriticForReviews = stoi(list[6]);
        tempm->duration = stoi(list[7]);

        tempm->gross = stoi(list[14]);
        tempm->numVotedUsers = stoi(list[15]);
        tempm->castTotalFacebookLikes = stoi(list[16]);
        tempm->faceNumberInPoster = stoi(list[17]);
        tempm->plotKeywords = list[18];
        tempm->movieImdbLink = list[19];
        tempm->numUserForReviews = stoi(list[20]);
        tempm->language = list[21];
        tempm->country = list[22];
        tempm->contentRating = list[23];
        tempm->budget = stod(list[24]);
        tempm->aspectRatio = stof(list[25]);
        tempm->movieFacebookLikes = stoi(list[26]);
        tempm->color = (list[27]);

        ml.InsertSortedMovies(tempm);                    //Movie inserted alphabetically into MovieList

        DirectorData *tempD = new DirectorData();        //Director object created which stores name nad info
        tempD->directorName = list[4];
        tempD->directorFacebookLikes = stoi(list[5]);
        tempD->moviesDirected->InsertAtEndm(tempm);
        tempm->director = tempD;
        dl.InsertSortedDirectors(tempD,
                                 tempm);            //movie created by director and director named added to respective lists


        ActorData *tempActor1 = new ActorData();        //Actor1 node
        tempActor1->actorName = list[8];
        tempActor1->actorFacebookLikes = stoi(list[9]);
        tempActor1->MoviesActedIn->InsertAtEndm(tempm);

        tempm->actors[0] = tempActor1;                    //actor added to actors array in MovieData

        ActorData *tempActor2 = new ActorData();        //Actor2 node
        tempActor2->actorName = list[10];
        tempActor2->actorFacebookLikes = stoi(list[11]);
        tempActor2->MoviesActedIn->InsertAtEndm(tempm);

        tempm->actors[1] = tempActor2;                    //actor added to actors array in MovieData

        ActorData *tempActor3 = new ActorData();        //Actor3 node
        tempActor3->actorName = list[12];
        tempActor3->actorFacebookLikes = stoi(list[13]);
        tempActor3->MoviesActedIn->InsertAtEndm(tempm);

        tempm->actors[2] = tempActor3;                    //actor added to actors array in MovieData

        //Actors, coActors and the movies they worked in added to their respective lists which
        //were created in actorData
        al.InsertSortedActors(tempActor1, tempm, tempActor2, tempActor3);
        al.InsertSortedActors(tempActor2, tempm, tempActor1, tempActor3);
        al.InsertSortedActors(tempActor3, tempm, tempActor1, tempActor2);

        i++;
    }
}

//prints the actors of searched movie name
// traverses through the movie list until required movie is found and prints its actors
// Big 0 compelxity is N
void MovieList::PrintActorsOfMovie(string name) {

    loc = start;
    while (loc != NULL) {

        if (upper_string(loc->pmData->movieTitle) ==
            upper_string(name)) {   //uppercase strings are compared and executes if names match
            cout << "Movie: " << loc->pmData->movieTitle << ".\t Actor1: " << loc->pmData->actors[0]->actorName
                 << " || Actor2: " << loc->pmData->actors[1]->actorName << " || Actor3: "
                 << loc->pmData->actors[2]->actorName << endl;
            return;
        }
        loc = loc->next;            //move to next node
    }
}

//prints the movies from movie list
//traverses movie list and prints the movieTitle data field
void MovieList::PrintMovieList() {

    MovieNode *temp;         //storing current node in temp ptr
    if (!MovieListIsEmpty()) {
        int i = 1;             //count variable
        temp = start;         //initialize the temp

        while (temp != NULL) { //looping till temp reaches end of list

            cout << "Movie " << i << ": " << temp->pmData->movieTitle << " || Released in " << temp->pmData->titleYear
                 << endl;
            temp = temp->next;    //moving to next node
            i++;
        }
    } else {
        cout << "List is Empty! " << endl;
    }
}

// prints movies with their titles years
// will be used in other functions
void MovieList::PrintMovieListInDetail() {

    MovieNode *temp;                    //storing current node in temp ptr
    if (!MovieListIsEmpty()) {
        int i = 1;                        //count variable
        temp = start;                    //initialize the temp
        while (temp != NULL) {            //looping till temp is not null
            cout << "Movie Node: " << i << ": " << temp->pmData->movieTitle << ". Which was realeased in "
                 << temp->pmData->titleYear << endl;
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is Empty! " << endl;
    }
}

//print co actors of certain actor
void MovieList::PrintCoActorMovieList(string ss) {
    MovieNode *temp; //storing current node in temp ptr
    string su = upper_string(ss);
    if (!MovieListIsEmpty()) {
        int i = 1;
        temp = start; //initialize the temp
        while (temp != NULL) { //looping till temp is not null
            cout << "Movie Node: " << i << ": " << temp->pmData->movieTitle;
            if (su != upper_string(temp->pmData->actors[0]->actorName)) {
                cout << ". CoActor : " << (temp->pmData->actors[0]->actorName) << " ";
            }
            if (su != upper_string(temp->pmData->actors[1]->actorName)) {
                cout << ". CoActor : " << (temp->pmData->actors[1]->actorName) << " ";
            }
            if (su != upper_string(temp->pmData->actors[2]->actorName)) {
                cout << ". CoActor : " << (temp->pmData->actors[2]->actorName);
            }
            cout << endl;
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is Empty! " << endl;
    }
}

//for co act co act function
// will be called in some document function 4 sub level
// traverses the list, if name matches then ignores, else prints the name(coactors)
// big 0 complexity is N
void MovieList::PrintCoActorssF4(string ss, string sx) {
    MovieNode *temp; //storing current node in temp ptr
    if (!MovieListIsEmpty()) {
        int i = 1;
        temp = start; //initialize the temp
        while (temp != NULL) { //looping till temp is not null
            if (ss != upper_string(temp->pmData->actors[0]->actorName)) {
                if (upper_string(temp->pmData->actors[0]->actorName) != sx) {
                    cout << ".Co CoActor : " << (temp->pmData->actors[0]->actorName) << "\n";
                }
            }
            if (ss != upper_string(temp->pmData->actors[1]->actorName)) {
                if (upper_string(temp->pmData->actors[1]->actorName) != sx) {
                    cout << ".Co CoActor : " << (temp->pmData->actors[1]->actorName) << "\n";
                }
            }
            if (ss != upper_string(temp->pmData->actors[2]->actorName)) {

                if (upper_string(temp->pmData->actors[2]->actorName) != sx) {
                    cout << ".Co CoActor : " << (temp->pmData->actors[2]->actorName) << "\n";
                }
            }
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is Empty! " << endl;
    }
}

//seacrhes for co actrs of the co actors
void MovieList::SearchCoActorCoActorMovieListlevel2(string ss, string sx) {
    MovieNode *temp; //storing current node in temp ptr
    if (!MovieListIsEmpty()) {
        int i = 1;
        temp = start; //initialize the temp
        while (temp != NULL) { //looping till temp is not null
            if (ss != upper_string(temp->pmData->actors[0]->actorName)) {
                temp->pmData->actors[0]->MoviesActedIn->PrintCoActorssF4(
                        upper_string(temp->pmData->actors[0]->actorName), sx);
            }
            if (ss != upper_string(temp->pmData->actors[1]->actorName)) {
                temp->pmData->actors[1]->MoviesActedIn->PrintCoActorssF4(
                        upper_string(temp->pmData->actors[1]->actorName), sx);
            }
            if (ss != upper_string(temp->pmData->actors[2]->actorName)) {
                temp->pmData->actors[2]->MoviesActedIn->PrintCoActorssF4(
                        upper_string(temp->pmData->actors[2]->actorName), sx);
            }
            temp = temp->next;
            i++;
        }
    } else {
        cout << "List is Empty! " << endl;
    }
}

// prints movies based on IMDB rating
//first time function is called, it checks if MovieList of Rating is empty or not
//if empty, all movies are inserted into that list in ascending order through while loop
//then RatingMovieList is printed

//BigO time complexity = N^2
//Big Omega time Complexity N

void MovieList::PrintMoviesRatingWise() {
    if (MovieListIsEmpty()) {
        cout << "Movie List is Empty. Cannot sort Rating Wise";
        return;
    }

    loc = start;
    ploc = NULL;

    if (mlRating.MovieListIsEmpty()) {
        mlRating.InsertAtFrontm(loc->pmData);

        mlRating.loc = mlRating.start;
        mlRating.ploc = NULL;

        ploc = loc;
        loc = loc->next;
    }
    while (loc != NULL) {

        mlRating.InsertSortedMoviesRating(loc->pmData);

        loc = loc->next;


    }
    mlRating.loc = mlRating.start->next;
    int i = 1;
    while (mlRating.loc != NULL) {
        cout << "Movie #" << i << ": " << mlRating.loc->pmData->movieTitle << " || Rating: "
             << mlRating.loc->pmData->imdbScore
             << endl;
        mlRating.loc = mlRating.loc->next;
        i++;
    }
}

// prints movies year wise in both descending and ascending order
//takes user input to determine if movies are to printed in ascending or descending years
//first time function is called, it checks if MovieList of Year is empty or not
//if empty, all movies are inserted into that list in ascending order through while loop
//and then user input is checked
//if bool is TRUE - Printing function is called and movies printed in ascending order
//if bool FALSE - recursive function is called which prints movies in descending order

//BigO time complexity = N^2
//Big Omega time Complexity N
void MovieList::PrintMoviesYearWise(bool printInAscendingYears) {

    bool isYearListEmpty = mlYear.MovieListIsEmpty();           //stores bool value if YearList is completely filled

    if (MovieListIsEmpty()) {                                        //if Original Movielist is empty, this function exits
        cout << "Movie List is Empty. Cannot sort Rating Wise";
        return;
    }

    loc = start;
    ploc = NULL;

    if (isYearListEmpty) {                                        //if YearList is empty, Movie inserted at front of that list
        mlYear.InsertAtFrontm(loc->pmData);
        mlYear.loc = mlYear.start;
        mlYear.ploc = NULL;
        ploc = loc;                                                //updating pointers
        loc = loc->next;
    }
    while (loc != NULL &&
           isYearListEmpty) {                        // executes if YearList is not completely filled or not and traverses entire MovieList while sorting based on year
        mlYear.InsertSortedMoviesYear(loc->pmData);
        loc = loc->next;                                        //moving to next node
    }

    mlYear.loc = mlYear.start->next;                            //resetting pointer position

    mlYear.printAscendingYears = printInAscendingYears;            //evaluating user input

    if (mlYear.printAscendingYears)
        while (mlYear.loc !=
               NULL) {                                //executes if TRUE - movies printed in ascending order
            cout << "Movie: " << mlYear.loc->pmData->movieTitle << " || Year: " << mlYear.loc->pmData->titleYear
                 << endl;
            mlYear.loc = mlYear.loc->next;
        }
    else {

        PrintMoviesInDescendingYear(mlYear.loc);                //recursive function to print movies in descending order

    }
    isYearListEmpty = mlYear.MovieListIsEmpty();                //bool updates , showing that YearList is populated completely now

}

// Recursive function to print movies in descending years
// function traverses to end of YearList and then prints the Title and Release Year
// BigO time complexity  = N
// Big Omega time complexity = N
void MovieList::PrintMoviesInDescendingYear(MovieNode *mn) {

    if (mn != NULL) {        //Base Case - executes till last node of list has been crossed

        PrintMoviesInDescendingYear(mn->next);  //moving nodes
        cout << "Movie: " << mn->pmData->movieTitle << " || Year: " << mn->pmData->titleYear << endl;
    }
}

// traverses a movie list for required movie and prints all of its contents
//prints all movies which match users input
// big 0 complexity is N
//Big Omega time complexity is N
void MovieList::PrintDetailsOfMovie(string name) {

    loc = start;
    valFound = false;                        //bool which determines if value has been found
    int i = 0;                                //count variable
    string uname = upper_string(name);        //uppercase sting saved

    while (loc != NULL) {                        //traverses through movie list

        if (upper_string(loc->pmData->movieTitle).find(uname) !=
            string::npos) { //if movie name matches, all of its details are printed
            valFound = true;
            cout << endl << "Search Result #" << ++i << endl;
            cout << "____" << endl;
            cout << "Movie: " << loc->pmData->movieTitle << endl
                 << "Released In: " << loc->pmData->titleYear << endl
                 << "Genres: " << loc->pmData->genres << endl
                 << "IMDB Score: " << loc->pmData->imdbScore << endl
                 << "Director: " << loc->pmData->director->directorName << endl
                 << "Director Likes: " << loc->pmData->director->directorFacebookLikes << endl
                 << "Actor #1 : " << loc->pmData->actors[0]->actorName << " || Facebook Likes: "
                 << loc->pmData->actors[0]->actorFacebookLikes << endl
                 << "Actor #2 : " << loc->pmData->actors[1]->actorName << " || Facebook Likes: "
                 << loc->pmData->actors[1]->actorFacebookLikes << endl
                 << "Actor #3 : " << loc->pmData->actors[2]->actorName << " || Facebook Likes: "
                 << loc->pmData->actors[2]->actorFacebookLikes << endl
                 << "Number of Critics for Reviews: " << loc->pmData->numCriticForReviews << endl
                 << "Duration: " << loc->pmData->duration << endl
                 << "Gross: $" << loc->pmData->gross << endl
                 << "Number of Users Voted: " << loc->pmData->numVotedUsers << endl
                 << "Total Cast Facebook Likes: " << loc->pmData->castTotalFacebookLikes << endl
                 << "Number of Faces In Poster: " << loc->pmData->faceNumberInPoster << endl
                 << "Plot Keywords: " << loc->pmData->plotKeywords << endl
                 << "Movie IMDB Link: " << loc->pmData->movieImdbLink << endl
                 << "Number of Users for Reviews: " << loc->pmData->numUserForReviews << endl
                 << "Language: " << loc->pmData->language << endl
                 << "Country: " << loc->pmData->country << endl
                 << "Content Rating: " << loc->pmData->contentRating << endl
                 << "Budget: $" << loc->pmData->budget << endl
                 << "Aspect Ratio: " << loc->pmData->aspectRatio << endl
                 << "Movie Facebook Likes: " << loc->pmData->movieFacebookLikes << endl
                 << "Movie Color: " << loc->pmData->color << endl;

        }

        loc = loc->next;  //moves to next node
    }

    if (!valFound)
        cout << "Movie \"" << name << "\" does not Exist!" << endl;  //lets user know movie does not exist
}

// prints directors who have directed movie of a certain genre
//access the DirectorList object and searches their MoviesDirected list
//The MoviesDirected list is traversed and the genre list is checked with user input
//if it matches, the directors name is printed and the next director in DirectorList goes through same process
//till end of DirectorList

//BigO Complexity(N^2)
//Big Omega Complexity (N*M)
//Since MoviesDirectedList and DirectorList are of different sizes

void MovieList::PrintDirectorsOfGenre(string genre) {
    dl.loc = dl.start->next;
    valFound = false;
    string genre_Upper = upper_string(genre);               //uppercase string saved
    int i = 0;

    while (dl.loc != NULL) {                                //loop goes through Director List
        MovieNode *movData = dl.loc->pData->moviesDirected->start;
        while (movData !=
               NULL) {                                             //loop goes through MoviesDirectedList of Current DirectorNode

            if (((upper_string(movData->pmData->genres)).find(genre_Upper) !=
                 string::npos)) {          //executes if genre matches in one of the direted movies
                if (!valFound) cout << endl << "Directors who have directed Movies for this Genre" << endl;

                valFound = true;
                cout << "Movie " << i++ << ": " << dl.loc->pData->directorName << endl;
                break;  //breaks to prevent repeating of director name

            }
            movData = movData->next;    //moving to next MovieDirectedList node
        }
        dl.loc = dl.loc->next;          //Moving to next DirectorList node
    }

    if (!valFound)
        cout << "No Director has Directed Movie for Genre:  \"" << genre << "\"" << endl;

}

//traverses through movie list and searches for movies that have genre which matches users input
//Big O time complexity N
//Big Omega time complexity N
void MovieList::PrintMoviesOfGenre(string genre) {
    loc = start;
    valFound = false;                            //bool which stores if movie with desired genre has been found

    string genre_Upper = upper_string(genre);    //stores uppercase string for comparison

    while (loc != NULL) {

        if ((upper_string(loc->pmData->genres)).find(genre_Upper) != string::npos) {
            if (!valFound) cout << endl << "Movies For This Genre:" << endl;        //prints Movies name
            valFound = true;

            cout << "Movie: " << loc->pmData->movieTitle << endl;

        }
        loc = loc->next;
    }

    if (!valFound)
        cout << "No Movie Exists For Genre:  \"" << genre << "\"" << endl;            //if genre did not match

}

//traverses through list and searches for movies that were released in year that matches users input
//Big O time complexity N
//Big Omega time complexity N
void MovieList::PrintMoviesOfYear(int year) {

    valFound = false;                            //bool which stores if movie with desired genre has been found
    loc = start;

    while (loc != NULL) {                            //loop makes nodes move to end of MovieList

        if (loc->pmData->titleYear == year) {        //if year matches - its Name and Year of Release is printed
            valFound = true;
            cout << "Movie: " << loc->pmData->movieTitle << "|| Released in " << year << endl;
        }
        loc = loc->next;                        //move to next node
    }
    if (!valFound) {
        cout << "No Movies were released in the year: " << year << endl;
    }
}

///////////////////////////////////////////////////////////////////
////-----------------------------MAIN--------------------------////
///////////////////////////////////////////////////////////////////

int main() {
    //reading contents of datafile
    PopulateStuff("IMDB_Cleaned.txt");            //file that is to be parsed
    int num = 0;
    cout << "Welcome to IMDB Database" << endl;

    while (true) {                                //text user interface to perform different functions;
        int userNumInput = 0;
        string userStringInput = "";
        string userStringInput2 = "";
        cout << "Input A Number To See Those Details. Input \"-1\" To Exit The Program" << endl;

        cout << endl << "1- Search profile of an actor" << endl;
        cout << "2- Search co-actors of an actor" << endl;
        cout << "3- Search unique co-actors and print them" << endl;
        cout << "4- Print a list of all co-actors of the co-actors of an actor" << endl;
        cout << "5- Search if 2 Actors are Co-Actors" << endl;
        cout << "6- Search A Director" << endl;
        cout << "7- Print Directors who have directed movies of a certain genre" << endl;
        cout << "8- Search a Movie and its Details" << endl;
        cout << "9- Search Movies Released in a Given Year" << endl;
        cout << "10-Print Movies year-wise" << endl;
        cout << "11-Search Movies Based on a Genre" << endl;
        cout << "12-Print Movies Rating Wise(from low to high)" << endl;

        cout << endl << "Your Choice(press the number): ";
        cin >> userNumInput;

        if (userNumInput > 12 || userNumInput < -1) {
            cout << "Invalid Number! Insert a Number between 1-12 or Enter -1 to Exit!" << endl;
            continue;
        }

        switch (userNumInput) {

            case -1:
                return 0;
                break;
            case 0:
                cout << "Invalid Number! Insert a Number between 1-12 or Enter -1 to Exit!" << endl;
                break;
            case 1:
                cout << "Enter The Actor whose Details You Want To See(movies he acted in): ";
                cin.ignore();
                getline(cin, userStringInput);
                al.SearchActorDetails(userStringInput);
                break;
            case 2:
                cout << "Enter The Actor whose Co-Actors You Want To See: ";
                cin.ignore();
                getline(cin, userStringInput);
                al.PrintCoActorDetails(userStringInput);
                break;
            case 3:
                cout << "Enter The Actor whose Co-Actors You Want To See: ";
                cin.ignore();
                getline(cin, userStringInput);
                al.PrintUniqueCoActors(userStringInput);
                break;
            case 4:
                cout << "Enter The Actor to see the Co-Actors of his Co-Actors: ";
                cin.ignore();
                getline(cin, userStringInput);
                al.SearchCoActorOfCoActor(userStringInput);
                break;
            case 5:
                cout << "Enter the name of 2 Actors to see if they are co-actors:" << endl;
                cout << "Actor 1: ";
                cin.ignore();
                getline(cin, userStringInput);
                cout << endl;
                cout << "Actor 2: ";
                getline(cin, userStringInput2);
                al.AreBothCoActors(userStringInput, userStringInput2);
                break;
            case 6:
                cout << "Enter the name of a director to see what movies they have directed: ";
                cin.ignore();
                getline(cin, userStringInput);
                dl.PrintMoviesDirectedBy(userStringInput);
                break;
            case 7:
                cout << "Enter a genre to see which directors have diected a movie of that genre";
                cin.ignore();
                getline(cin, userStringInput);
                ml.PrintDirectorsOfGenre(userStringInput);
                break;
            case 8:
                cout << "Enter name of a movie to see it's details: ";
                cin.ignore();
                getline(cin, userStringInput);
                ml.PrintDetailsOfMovie(userStringInput);
                break;
            case 9:
                cout << "Enter a Year to see movies released in that year: ";
                cin >> userNumInput;
                ml.PrintMoviesOfYear(userNumInput);
                break;
            case 10:
                cout
                        << "Press '1' to see movies released, in ascending order. Press '2' to see movies released, in descending order: ";
                cin >> userNumInput;
                if (userNumInput == 1)
                    ml.PrintMoviesYearWise(true);
                else if (userNumInput == 2)
                    ml.PrintMoviesYearWise(false);
                else
                    cout << "Invalid Input!" << endl;
                break;
            case 11:
                cout << "Enter a genre to see a list of movies of that genre: ";
                cin.ignore();
                getline(cin, userStringInput);
                ml.PrintMoviesOfGenre(userStringInput);
                break;
            case 12:
                cout << "Movies Sorted Rating Wise!" << endl;
                ml.PrintMoviesRatingWise();
                break;

        }
        system("pause");
    }

}