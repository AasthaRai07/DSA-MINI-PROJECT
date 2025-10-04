#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE 50
#define MAX_KEYWORD 20
#define MAX_POSTS 20

typedef struct {
    int id;
    char title[MAX_TITLE];
    char keyword[MAX_KEYWORD];
    int likes;
    int comments;
    int timestamp;
    int score;
} Post;

Post posts[MAX_POSTS];
int postCount = 0;
char userInterest[MAX_KEYWORD];

// compute ranking score
int compute_score(Post p) {
    int keyword_match = (strcmp(p.keyword, userInterest) == 0) ? 1 : 0;
    return (2 * p.likes) + (3 * p.comments) + (5 * keyword_match) + (p.timestamp % 10);
}

// sort posts by score (descending)
void sort_posts() {
    for(int i = 0; i < postCount-1; i++) {
        for(int j = i+1; j < postCount; j++) {
            if(posts[i].score < posts[j].score) {
                Post temp = posts[i];
                posts[i] = posts[j];
                posts[j] = temp;
            }
        }
    }
}

// display posts like a table
void display_posts() {
    if(postCount == 0) {
        printf("\nNo posts available!\n");
        return;
    }

    sort_posts();

    printf("\n===================================================\n");
    printf("           NEWS FEED RANKING SYSTEM\n");
    printf("===================================================\n");
    printf("%-5s %-20s %-8s %-8s %-10s %-6s\n", 
           "Rank", "Title", "Likes", "Comments", "Keyword", "Score");
    printf("---------------------------------------------------\n");

    for(int i = 0; i < postCount; i++) {
        printf("%-5d %-20s %-8d %-8d %-10s %-6d\n", 
               i+1, posts[i].title, posts[i].likes, posts[i].comments, posts[i].keyword, posts[i].score);
    }
    printf("---------------------------------------------------\n");
}

// add a new post
void add_post() {
    if(postCount >= MAX_POSTS) {
        printf("\nPost limit reached!\n");
        return;
    }

    Post p;
    p.id = postCount + 1;

    printf("\nEnter post title: ");
    scanf(" %[^\n]", p.title);

    printf("Enter keyword: ");
    scanf("%s", p.keyword);

    printf("Enter number of likes: ");
    scanf("%d", &p.likes);

    printf("Enter number of comments: ");
    scanf("%d", &p.comments);

    p.timestamp = time(NULL);
    p.score = compute_score(p);

    posts[postCount++] = p;

    printf("\n✅ Post added successfully!\n");
}

// set user interest
void set_interest() {
    printf("\nEnter your interest keyword: ");
    scanf("%s", userInterest);

    // update scores for all posts
    for(int i = 0; i < postCount; i++) {
        posts[i].score = compute_score(posts[i]);
    }
    printf("✅ Interest updated!\n");
}

int main() {
    int choice;

    printf("=====================================\n");
    printf("   WELCOME TO NEWS FEED RANKING APP\n");
    printf("=====================================\n");

    strcpy(userInterest, "general");  // default interest

    while(1) {
        printf("\n========= MENU =========\n");
        printf("1. Add Post\n");
        printf("2. View Ranked Feed\n");
        printf("3. Set Interest Keyword\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: add_post(); break;
            case 2: display_posts(); break;
            case 3: set_interest(); break;
            case 4: printf("\nExiting... Goodbye!\n"); exit(0);
            default: printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

