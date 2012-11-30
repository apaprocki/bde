// bslmf_isvoid.t.cpp                                                 -*-C++-*-
#include <bslmf_isvoid.h>

#include <bsls_bsltestutil.h>

#include <stdio.h>      // sprintf()
#include <stdlib.h>     // atoi()

using namespace BloombergLP;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// The component under test defines two meta-functions, 'bsl::is_void' and
// 'bslmf::IsVoid', that determine whether a template parameter type is a
// pointer type.  Thus, we need to ensure that the values returned by these
// meta-functions are correct for each possible category of types.  Since the
// two meta-functions are functionally equivalent, we will use the same set of
// types for both.
//
//-----------------------------------------------------------------------------
// [ 4] bslmf::IsVoid conversion to bool
// [ 4] bslmf::IsVoid conversion to bslmf::MetaInt
// [ 3] bslmf::IsVoid::Type
// [ 2] bslmf::IsVoid::VALUE
// [ 2] bsl::is_void::value
//-----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [ 5] USAGE EXAMPLE
//=============================================================================
//                       STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.
static int testStatus = 0;

void aSsErT(bool b, const char *s, int i)
{
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

# define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

//=============================================================================
//                    GLOBAL CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

bool globalVerbose         = false;
bool globalVeryVerbose     = false;
bool globalVeryVeryVerbose = false;

//=============================================================================
//                  GLOBAL HELPER MACROS FOR TESTING
//-----------------------------------------------------------------------------
// These standard aliases will be defined below as part of the usage example.

//=============================================================================
//                  GLOBAL HELPER FUNCTIONS FOR TESTING
//-----------------------------------------------------------------------------
namespace
{
struct Empty {
    // This 'struct' is an empty dummy type to allow formation of pointer-to-
    // member types for testing.  Note that as all such uses expected for
    // testing this component will be initialized only with null values, there
    // is no need for any actual members to point to.
};

template<class TYPE>
struct Identity {
    // This metafunction provides a type-dependent context for testing the
    // behavior of type traits.

    typedef TYPE Type;
};

struct Incomplete;
    // A forward declaration for the type that shall remain incomplete for this
    // whole translation unit.  This is provided solely for the purpose of
    // testing the 'bslmf::IsVoid' metafunction with incomplete types.

template<int N>
bool dispatchFalseType(...)                 { return false; }
bool dispatchFalseType(bsl::false_type)     { return true;  }

template<int N>
bool dispatchTrueType(...)                  { return false; }
bool dispatchTrueType(bsl::true_type)       { return true;  }


template<class PREDICATE>
bool isFalseType() { return false; }

template<>
bool isFalseType<bsl::false_type>() { return true; }

template<class PREDICATE>
bool isTrueType() { return false; }

template<>
bool isTrueType<bsl::true_type>() { return true; }

template<class TYPE>
bool typeDependentTest()
{
    // Check that the 'bslmf::IsVoid' metafunction returns a consistent result
    // for template parameters, and when applied to the same type parameter in
    // a type-dependent context.  Return the diagnosed value for the specified
    // 'TYPE'.
    bool result = bslmf::IsVoid<TYPE>::value;
    bool dependentCheck = bslmf::IsVoid<typename Identity<TYPE>::Type>::value;
    LOOP2_ASSERT(result, dependentCheck, result == dependentCheck);
    return result;
}

template<class TYPE>
bool isDependentFalseType()
{
    // Check that the 'bslmf::IsVoid' metafunction returns a consistent result
    // for template parameters, and when applied to the same type parameter in
    // a type-dependent context.  Return the diagnosed value for the specified
    // 'TYPE'.
    ASSERT(isFalseType<typename bslmf::IsVoid<TYPE>::type>());
    return isFalseType<
                typename bslmf::IsVoid<typename Identity<TYPE>::Type>::type>();
}

template<class TYPE>
bool isDependentTrueType()
{
    // Check that the 'bslmf::IsVoid' metafunction returns a consistent result
    // for template parameters, and when applied to the same type parameter in
    // a type-dependent context.  Return the diagnosed value for the specified
    // 'TYPE'.
    ASSERT(isTrueType<typename bslmf::IsVoid<TYPE>::type>());
    return isTrueType<
                typename bslmf::IsVoid<typename Identity<TYPE>::Type>::type>();
}


template<class TYPE>
bool dispatchDependentFalseType()
{
    // Check that the 'bslmf::IsVoid' metafunction returns a consistent result
    // for template parameters, and when applied to the same type parameter in
    // a type-dependent context.  Return the diagnosed value for the specified
    // 'TYPE'.
    return dispatchFalseType(bslmf::IsVoid<TYPE>());

}

template<class TYPE>
bool dispatchDependentTrueType()
{
    // Check that the 'bslmf::IsVoid' metafunction returns a consistent result
    // for template parameters, and when applied to the same type parameter in
    // a type-dependent context.  Return the diagnosed value for the specified
    // 'TYPE'.
    return dispatchTrueType(bslmf::IsVoid<TYPE>());

}

}  // close unnamed namespace
//=============================================================================
//                                MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;

    setbuf(stdout, 0);    // Use unbuffered output

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:
      case 5: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) printf("\nUSAGE EXAMPLE"
                            "\n=============\n");
///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Verify Pointer Types
///- - - - - - - - - - - - - - - -
// Suppose that we want to assert whether a particular type is a void type.
//
// First, we create two 'typedef's -- a void type and another type:
//..
        typedef int  MyType;
        typedef void MyVoidType;
//..
// Now, we instantiate the 'bsl::is_void' template for each of the
// 'typedef's and assert the 'value' static data member of each instantiation:
//..
        ASSERT(false == bsl::is_void<MyType>::value);
        ASSERT(true == bsl::is_void<MyVoidType>::value);
//..

      } break;
      case 4: {
        // --------------------------------------------------------------------
        // TESTING type conversion:
        // Concerns:
        //: 1 Objects of type 'bslmf::IsVoid' are unambiguously convertible to
        //:   either 'bslmf::MetaInt<0>' or 'bslmf::MetaInt<1>', supporting tag
        //:   dispatch.
        //: 2 Such objects are convertible to 'bslmf::MetaInt<1>' if the
        //:   parameterized type is a cv-qualified 'void' type, and
        //:   'bslmf::MetaInt<0>' otherwise.
        //: 3 Such objects are contextually convertible to the boolean value
        //:   'true' if the parameterized type is a cv-qualified 'void' type,
        //:   and 'false' otherwise.
        //: 4 Such conversions produce the correct result, even in type-
        //:   dependent contexts.
        //
        // Plan:
        //
        // Testing:
        //   conversion to 'bslmf::MetaInt<>'
        //   conversion to 'bool'
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING conversion to bslmf_MetaInt"
                            "\n====================================\n");

        // Basic test dataset
        ASSERT(dispatchTrueType(bslmf::IsVoid<void>()));
        ASSERT(dispatchTrueType(bslmf::IsVoid<const void>()));
        ASSERT(dispatchTrueType(bslmf::IsVoid<volatile void>()));
        ASSERT(dispatchTrueType(bslmf::IsVoid<const volatile void>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<void *>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<void *&>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<void()>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<void(*)()>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<void *Empty::*>()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<bslmf::IsVoid<void> >()));
        ASSERT(dispatchFalseType(bslmf::IsVoid<Incomplete>()));

        // Basic test dataset for 'bool' conversion
        // Note that this test is C++03 specific, and should fail to compile
        // with C++11 where such conversions will be 'explicit'.  This set of
        // tests should check use in an 'if' statement instead.
        ASSERT(bslmf::IsVoid<void>());
        ASSERT(bslmf::IsVoid<const void>());
        ASSERT(bslmf::IsVoid<volatile void>());
        ASSERT(bslmf::IsVoid<const volatile void>());
        ASSERT(!bslmf::IsVoid<void *>());
        ASSERT(!bslmf::IsVoid<void *&>());
        ASSERT(!bslmf::IsVoid<void()>());
        ASSERT(!bslmf::IsVoid<void(*)()>());
        ASSERT(!bslmf::IsVoid<void *Empty::*>());
        ASSERT(!bslmf::IsVoid<bslmf::IsVoid<void> >());
        ASSERT(!bslmf::IsVoid<Incomplete>());

        // Test type-dependent typenames with the same dataset
        ASSERT(dispatchDependentTrueType<void>());
        ASSERT(dispatchDependentTrueType<const void>());
        ASSERT(dispatchDependentTrueType<volatile void>());
        ASSERT(dispatchDependentTrueType<const volatile void>());
        ASSERT(dispatchDependentFalseType<void *>());
        ASSERT(dispatchDependentFalseType<void *&>());
        ASSERT(dispatchDependentFalseType<void()>());
        ASSERT(dispatchDependentFalseType<void(*)()>());
        ASSERT(dispatchDependentFalseType<void *Empty::*>());
        ASSERT(dispatchDependentFalseType<bslmf::IsVoid<void> >());
        ASSERT(dispatchDependentFalseType<Incomplete>());
      } break;
      case 3: {
        // --------------------------------------------------------------------
        // TESTING bslmf::IsVoid metafunction:
        // Concerns:
        //: 1 The metafunction 'bslmf::IsVoid' contains a nested type alias
        //:   named 'Type'.
        //: 2 The alias 'Type' is unambiguously either 'bslmf::MetaInt<0>' or
        //:   'bslmf::MetaInt<1>'.
        //: 3 The nested type alias is 'bslmf::MetaInt<1>' if the parameterized
        //:   type is a cv-qualified 'void' type, and 'bslmf::MetaInt<0>'
        //:   otherwise.
        //: 4 The nested typename correctly reports that aliases and template
        //:   type parameters corresponding to cv-qualified 'void' types are
        //:   also void.
        //: 5 The nested typename produces the correct result, even in type-
        //:   dependent contexts.
        //
        // Plan:
        //
        // Testing:
        //   bslmf::IsVoid::type
        // --------------------------------------------------------------------

        if (verbose) printf("\nTESTING bslmf::IsVoid::type"
                            "\n===========================\n");

        // Basic test dataset
        ASSERT(isTrueType<bslmf::IsVoid<void>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<const void>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<volatile void>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<const volatile void>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<void *>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<void *&>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<void()>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<void(*)()>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<void *Empty::*>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<bslmf::IsVoid<void> >::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Incomplete>::type>());

        // Test nested template typenames with the same dataset
        ASSERT(isTrueType<bslmf::IsVoid<Identity<void>::Type>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<Identity<const void>::Type>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<
                                      Identity<volatile void>::Type>::type>());
        ASSERT(isTrueType<bslmf::IsVoid<
                                Identity<const volatile void>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Identity<void *>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Identity<void *&>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Identity<void()>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Identity<void(*)()>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<
                                     Identity<void *Empty::*>::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<
                               Identity<bslmf::IsVoid<void> >::Type>::type>());
        ASSERT(isFalseType<bslmf::IsVoid<Identity<Incomplete>::Type>::type>());

        // Test type-dependent typenames with the same dataset
        ASSERT(isDependentTrueType<void>());
        ASSERT(isDependentTrueType<const void>());
        ASSERT(isDependentTrueType<volatile void>());
        ASSERT(isDependentTrueType<const volatile void>());
        ASSERT(isDependentFalseType<void *>());
        ASSERT(isDependentFalseType<void *&>());
        ASSERT(isDependentFalseType<void()>());
        ASSERT(isDependentFalseType<void(*)()>());
        ASSERT(isDependentFalseType<void *Empty::*>());
        ASSERT(isDependentFalseType<bslmf::IsVoid<void> >());
        ASSERT(isDependentFalseType<Incomplete>());
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // bslmf::IsVoid::VALUE and bsl::is_void::value
        // Concerns:
        //: 1 The metafunctions returns 'true' for any 'void' type, regardless
        //:   of its cv-qualification.
        //: 2 The metafunctions returns 'false' for every other type.
        //: 3 The metafunctions returns the correct result, even when the
        //:   potentially 'void' type it is diagnosing is a type alias, such as
        //:   a dependent type name in a template.
        //
        // Plan:
        //   Verify that both 'bsl::is_void::value' and 'bslmf::IsVoid::VALUE'
        //   has the correct value for each concern.
        //
        // Testing:
        //   bslmf::IsVoid::VALUE
        //   bsl::is_void::value
        // --------------------------------------------------------------------

        if (verbose)
            printf("\nbslmf::IsVoid::VALUE and bsl::is_void::value\n"
                   "\n============================================\n");

        // Basic test dataset
        ASSERT( bslmf::IsVoid<void>::VALUE);
        ASSERT( bslmf::IsVoid<const void>::VALUE);
        ASSERT( bslmf::IsVoid<volatile void>::VALUE);
        ASSERT( bslmf::IsVoid<const volatile void>::VALUE);
        ASSERT(!bslmf::IsVoid<void *>::VALUE);
        ASSERT(!bslmf::IsVoid<void *&>::VALUE);
        ASSERT(!bslmf::IsVoid<void()>::VALUE);
        ASSERT(!bslmf::IsVoid<void(*)()>::VALUE);
        ASSERT(!bslmf::IsVoid<void *Empty::*>::VALUE);
        ASSERT(!bslmf::IsVoid<bslmf::IsVoid<void> >::VALUE);
        ASSERT(!bslmf::IsVoid<Incomplete>::VALUE);

        ASSERT( bsl::is_void<void>::value);
        ASSERT( bsl::is_void<const void>::value);
        ASSERT( bsl::is_void<volatile void>::value);
        ASSERT( bsl::is_void<const volatile void>::value);
        ASSERT(!bsl::is_void<void *>::value);
        ASSERT(!bsl::is_void<void *&>::value);
        ASSERT(!bsl::is_void<void()>::value);
        ASSERT(!bsl::is_void<void(*)()>::value);
        ASSERT(!bsl::is_void<void *Empty::*>::value);
        ASSERT(!bsl::is_void<bsl::is_void<void> >::value);
        ASSERT(!bsl::is_void<Incomplete>::value);

        // Test nested template typenames with the same dataset
        ASSERT( bslmf::IsVoid<Identity<void>::Type>::VALUE);
        ASSERT( bslmf::IsVoid<Identity<const void>::Type>::VALUE);
        ASSERT( bslmf::IsVoid<Identity<volatile void>::Type>::VALUE);
        ASSERT( bslmf::IsVoid<Identity<const volatile void>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<void *>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<void *&>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<void()>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<void(*)()>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<void *Empty::*>::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<bslmf::IsVoid<void> >::Type>::VALUE);
        ASSERT(!bslmf::IsVoid<Identity<Incomplete>::Type>::VALUE);

        ASSERT( bsl::is_void<Identity<void>::Type>::value);
        ASSERT( bsl::is_void<Identity<const void>::Type>::value);
        ASSERT( bsl::is_void<Identity<volatile void>::Type>::value);
        ASSERT( bsl::is_void<Identity<const volatile void>::Type>::value);
        ASSERT(!bsl::is_void<Identity<void *>::Type>::value);
        ASSERT(!bsl::is_void<Identity<void *&>::Type>::value);
        ASSERT(!bsl::is_void<Identity<void()>::Type>::value);
        ASSERT(!bsl::is_void<Identity<void(*)()>::Type>::value);
        ASSERT(!bsl::is_void<Identity<void *Empty::*>::Type>::value);
        ASSERT(!bsl::is_void<Identity<bsl::is_void<void> >::Type>::value);
        ASSERT(!bsl::is_void<Identity<Incomplete>::Type>::value);

        // Test type-dependent typenames with the same dataset
        ASSERT(typeDependentTest<void>());
        ASSERT(typeDependentTest<const void>());
        ASSERT(typeDependentTest<volatile void>());
        ASSERT(typeDependentTest<const volatile void>());
        ASSERT(!typeDependentTest<void *>());
        ASSERT(!typeDependentTest<void *&>());
        ASSERT(!typeDependentTest<void()>());
        ASSERT(!typeDependentTest<void(*)()>());
        ASSERT(!typeDependentTest<void *Empty::*>());
        ASSERT(!typeDependentTest<bslmf::IsVoid<void> >());
        ASSERT(!typeDependentTest<Incomplete>());

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //   This case exercises (but does not fully test) basic functionality.
        //
        // Concerns:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases.
        //
        // Plan:
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) printf("\nBREATHING TEST"
                            "\n==============\n");

        ASSERT(bslmf::IsVoid<void>::value);
        ASSERT(!bslmf::IsVoid<int>::value);

      } break;
      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }

    return testStatus;
}
// ----------------------------------------------------------------------------
// Copyright (C) 2012 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------
