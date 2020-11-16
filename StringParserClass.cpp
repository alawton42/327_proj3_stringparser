/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

//TODO Fill in
using namespace KP_StringParserClass;

StringParserClass::StringParserClass(void){
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

StringParserClass::~StringParserClass(void){
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	pStartTag = new char[strlen(pStart)];
	strcpy(pStartTag, pStart);

	pEndTag = new char[strlen(pEnd)];
	strcpy(pEndTag, pEnd);

	areTagsSet = true;
	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
	if(pStartTag == NULL || pEndTag == NULL){
		return ERROR_TAGS_NULL;
	}

	if(pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}

	myVector.clear();
	bool insideTags = false;
	std::string text = "";
	for(unsigned int i = 0; i < strlen(pDataToSearchThru); i++){
		if(!insideTags && *(pDataToSearchThru + i) == pStartTag[0]){
			if (strncmp((pDataToSearchThru + i), pStartTag, strlen(pStartTag)) == 0){
				insideTags = true;
				i += strlen(pStartTag);
			}
		}

		if(insideTags && *(pDataToSearchThru + i) == pEndTag[0]){
			if (strncmp((pDataToSearchThru + i), pEndTag, strlen(pEndTag)) == 0){
				myVector.push_back(text);
				text.clear();
				insideTags = false;
				i += strlen(pEndTag) - 1;
			}
		}

		if(insideTags){
			text += *(pDataToSearchThru + i);
		}
	}

	return SUCCESS;
}

void StringParserClass::cleanup(){
	if(pStartTag){
			delete [] pStartTag;
		}

		if(pEndTag){
			delete [] pEndTag;
		}

		areTagsSet = false;
}

int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}

	for(unsigned int i = 0; i < strlen(pStart); i++){
		if(*(pStart + i) == pTagToLookFor[0]){
			if(strncmp((pStart + i), pTagToLookFor, strlen(pTagToLookFor)) == 0){
				pStart += i;
				pEnd = pStart + strlen(pTagToLookFor) + i - 1;
				return SUCCESS;
			}
		}
	}
	return FAIL;
}


