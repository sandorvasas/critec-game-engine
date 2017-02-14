
#ifndef __CRITEC_GAMELEVEL_H_
#define __CRITEC_GAMELEVEL_H_

class crPlayerCamera;
class cr3DSModel;
class crStr;
class crVec2;

typedef struct __crLevelNode {
	int					iType;
	unsigned int		uiParent;
	unsigned int		uiChildren[4];

} crLevelNode, *pcrLevelNode;


class crGameLevel : public cr3DSModel {

protected:
	pcrLevelNode		nodes;
	crStr				name;


	void				Render( crPlayerCamera* camera,  bool optimized = true );
};

#endif /* __CRITEC_GAMELEVEL_H_ */