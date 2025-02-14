from movies import movie_dataset, movie_ratings

def distance(movie1, movie2):
    squared_difference = 0
    for i in range(len(movie1)):
        squared_difference += (movie1[i] - movie2[i]) ** 2
        final_distance = squared_difference ** 0.5
    return final_distance

def predict(unknown, dataset, movie_ratings, k):
    distances = []
    #Looping through all points in the dataset
    for title in dataset:
        movie = dataset[title]
        distance_to_point = distance(movie, unknown)
        #Adding the distance and point associated with that distance
        distances.append([distance_to_point, title])
    distances.sort()
    #Taking only the k closest points
    neighbors = distances[0:k]


    numerator = 0
    denominator = 0

    for neighbor in neighbors:
        if neighbor[0] <= 1:
          weight = 1
        else:
          weight = neighbor[0]
        numerator += movie_ratings[neighbor[1]]/weight
        denominator += 1/weight

    return numerator/denominator

print(predict([0.016, 0.300, 1.022], movie_dataset, movie_ratings, 5))
print(predict(movie_dataset['Life of Pi'], movie_dataset, movie_ratings, 5))

