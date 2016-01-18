

#ifndef __SOP_Smoke_Source_h__
#define __SOP_Smoke_Source_h__

#include <SOP/SOP_Node.h>

namespace HDK_Sample {
class SOP_Smoke_Source : public SOP_Node
{
public:
	     SOP_Smoke_Source(OP_Network *net, const char *name, OP_Operator *op);
    virtual ~SOP_Smoke_Source();

    /// This method is created so that it can be called by handles.  It only
    /// cooks the input group of this SOP.  The geometry in this group is
    /// the only geometry manipulated by this SOP.
    virtual OP_ERROR		 cookInputGroups(OP_Context &context, 
						int alone = 0);

    static PRM_Template		 myTemplateList[];
    static OP_Node		*myConstructor(OP_Network*, const char *,
							    OP_Operator *);

protected:
    /// Update disable and hidden states of parameters based on the value
    /// of other parameters.
    virtual bool		 updateParmsFlags();

    virtual const char          *inputLabel(unsigned idx) const;

    /// Method to cook geometry for the SOP
    virtual OP_ERROR		 cookMySop(OP_Context &context);

    /// This method is used to generate geometry for a "guide".  It does
    ///	not have to be defined.
    virtual OP_ERROR             cookMyGuide1(OP_Context &context);

private:
    void	getGroups(UT_String &str){ evalString(str, "group", 0, 0); }
    fpreal	DIST(fpreal t)		{ return evalFloat("dist", 0, t); }
    int		DIRPOP()		{ return evalInt("usedir", 0, 0); }
    int		ORIENT()		{ return evalInt("orient", 0, 0); }
    fpreal	NX(fpreal t)		{ return evalFloat("dir", 0, t); }
    fpreal	NY(fpreal t)		{ return evalFloat("dir", 1, t); }
    fpreal	NZ(fpreal t)		{ return evalFloat("dir", 2, t); }

    /// This is the group of geometry to be manipulated by this SOP and cooked
    /// by the method "cookInputGroups".
    const GA_PointGroup *myGroup;
};
} // End HDK_Sample namespace

#endif
