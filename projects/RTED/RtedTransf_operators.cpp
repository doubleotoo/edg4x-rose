#include <rose.h>

// DQ (2/9/2010): Testing use of ROE to compile ROSE.
#ifndef USE_ROSE

#include "RtedSymbols.h"
#include "DataStructures.h"
#include "RtedTransformation.h"

using namespace SageInterface;
using namespace SageBuilder;

void RtedTransformation::visit_pointer_movement( SgNode* node ) {
    SgUnaryOp* u_op = isSgUnaryOp( node );
    SgBinaryOp* b_op = isSgBinaryOp( node );
    ROSE_ASSERT( u_op || b_op );

    SgExpression* operand = NULL;
    if( u_op )
        operand = u_op -> get_operand();
    else if( b_op )
        operand = b_op -> get_lhs_operand();

    if( !isUsableAsSgPointerType( operand -> get_type() ))
        // we don't care about int++, only pointers, or reference to pointers.
        return;

    pointer_movements.push_back( isSgExpression( node ));
}


void RtedTransformation::insert_pointer_change( SgExpression* exp ) {
    SgUnaryOp* u_op = isSgUnaryOp( exp );
    SgBinaryOp* b_op = isSgBinaryOp( exp );
    ROSE_ASSERT( u_op || b_op );
    SgStatement* stmt = getSurroundingStatement( exp );
    ROSE_ASSERT( stmt );

    SgExpression*  operand = u_op ? u_op -> get_operand() : b_op -> get_lhs_operand();
    SgExprListExp* mp_args = buildExprListExp();

    appendExpression( mp_args, ctorTypeDesc(mkTypeInformation(NULL, operand -> get_type())) );
    appendAddress( mp_args, operand );
    appendClassName( mp_args, operand -> get_type() );
    appendFileInfo( mp_args, exp );

    ROSE_ASSERT(symbols.roseMovePointer);
    SgExprStatement* mp_call =
            buildFunctionCallStmt(
                buildFunctionRefExp( symbols.roseMovePointer ),
                mp_args
            );

    insertStatementAfter( stmt, mp_call );
    attachComment( mp_call, "", PreprocessingInfo::before );
    attachComment(
        mp_call,
        "RS : movePointer , parameters : ( address, type, base_type, indirection_level, class_name, filename, lineno, linetransformed)",
        PreprocessingInfo::before
    );
}



void RtedTransformation::visit_delete( SgDeleteExp* del ) {
  // FIXME 2: this is wrong if delete is overloaded
  frees.push_back( del );
}

#endif
