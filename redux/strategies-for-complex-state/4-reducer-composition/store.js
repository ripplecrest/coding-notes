import { createStore } from 'redux';
import allRecipesData from './data.js';

// Action Creators
////////////////////////////////////////

const addRecipe = (recipe) => {
    return {
        type: 'favoriteRecipes/addRecipe',
        payload: recipe
    };
};

const removeRecipe = (recipe) => {
    return {
        type: 'favoriteRecipes/removeRecipe',
        payload: recipe
    };
};

const setSearchTerm = (term) => {
    return {
        type: 'searchTerm/setSearchTerm',
        payload: term
    };
};

const clearSearchTerm = () => {
    return {
        type: 'searchTerm/clearSearchTerm'
    };
};

const loadData = () => {
    return {
        type: 'allRecipes/loadData',
        payload: allRecipesData
    };
};

// Reducers
////////////////////////////////////////

const initialAllRecipes = [];
const allRecipesReducer = (allRecipes = initialAllRecipes, action) => {
    switch(action.type) {
    case 'allRecipes/loadData':
        return action.payload;
    default:
        return allRecipes;
    }
};

const initialSearchTerm = '';

const searchTermReducer = (searchTerm = initialSearchTerm, action) => {
    switch(action.type) {
    case 'searchTerm/setSearchTerm':
        return action.payload;
    case 'searchTerm/clearSearchTerm':
        return '';
    default:
        return searchTerm;
    }
};

const initialFavoriteRecipes  = [];

// Create the initial state for this reducer.
const favoriteRecipesReducer = (favoriteRecipes = initialFavoriteRecipes, action) => {
    switch(action.type) {

        // Add action.type cases here.

        // Don't forget to set the default case!

    }
};


const rootReducer = (state = {}, action) => {
    const nextState = {
        allRecipes: allRecipesReducer(state.allRecipes, action),
        searchTerm: searchTermReducer(state.searchTerm, action),
        // Add in the favoriteRecipes slice using the
        // favoriteRecipesReducer function.
    };
    return nextState;
};

const store = createStore(rootReducer);
