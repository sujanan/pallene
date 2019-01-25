/*
 *  This implements some manual optimizations that the pallene compiler
 *  currently cannot. See "HANDOPT.txt".
 */

/*
 *  This file also removes all safety tag checks
 */

/* This file was generated by the Pallene compiler. Do not edit by hand */
/* Indentation and formatting courtesy of pallene/pretty.lua */

#include <string.h>

#include "pallene_core.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "lapi.h"
#include "lfunc.h"
#include "lgc.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "lvm.h"

#include "math.h"

static Table * function_new_pallene(
    lua_State * L,
    lua_Number x1 /* x */,
    lua_Number x2 /* y */
){
    CClosure * x3 = clCvalue(s2v(L->ci->func));
    Udata * x4 /* upvalue table */ = uvalue(&x3->upvalue[0]);
    UValue * x5 /* upvalue array */ = x4->uv;
    (void)x5;
    {
        luaC_condGC(L, {
        }, {
        });
        Table * x6 = luaH_new(L);
        luaH_resizearray(L, x6, 2);
        TValue * x7 = x6->array;
        setfltvalue(x7 + 0, x1);
        setfltvalue(x7 + 1, x2);
        return x6;
    }
}

static int function_new_lua(lua_State *L)
{
    lua_checkstack(L, 1);
    CClosure * x1 = clCvalue(s2v(L->ci->func));
    Udata * x2 /* upvalue table */ = uvalue(&x1->upvalue[0]);
    UValue * x3 /* upvalue array */ = x2->uv;
    (void)x3;
    StackValue* x4 = L->ci->func;
    lua_Number x8 = fltvalue(s2v(x4 + 1));
    lua_Number x9 = fltvalue(s2v(x4 + 2));
    Table * x10 /* ret */ = function_new_pallene(L, x8, x9);
    sethvalue(L, s2v(L->top), x10);
    api_incr_top(L);
    return 1;
}

static Table * function_centroid_pallene(
    lua_State * L,
    Table * x1 /* points */,
    lua_Integer x2 /* nrep */
){
    lua_checkstack(L, 1);
    CClosure * x3 = clCvalue(s2v(L->ci->func));
    Udata * x4 /* upvalue table */ = uvalue(&x3->upvalue[0]);
    UValue * x5 /* upvalue array */ = x4->uv;
    (void)x5;
    {
        lua_Number x6 /* x */ = 0x0p+0 /*0.000000*/;
        lua_Number x7 /* y */ = 0x0p+0 /*0.000000*/;
        lua_Integer x8 = luaH_getn(x1);
        lua_Integer x9 /* npoints */ = x8;
        lua_Integer x10 /* start */ = 1;
        lua_Integer x11 /* limit */ = x2;
        lua_Integer x12 /* step */ = 1;
        while ((x12 >= 0 ? x10 <= x11 : x10 >= x11)) {
            lua_Integer x13 /* _ */ = x10;
            (void) x13;
            {
                x6 = 0x0p+0 /*0.000000*/;
                x7 = 0x0p+0 /*0.000000*/;
                lua_Integer x14 /* start */ = 1;
                lua_Integer x15 /* limit */ = x9;
                lua_Integer x16 /* step */ = 1;

                /* BEGIN OPT - bounds for */
                {
                    lua_Unsigned bound = ((lua_Unsigned)x15) - 1;
                    if (PALLENE_UNLIKELY(bound >= x1->sizearray)) {
                        pallene_renormalize_array(L, x1, bound, 19);
                    }
                }
                /* END OPT */
                while ((x16 >= 0 ? x14 <= x15 : x14 >= x15)) {
                    lua_Integer x17 /* i */ = x14;
                    (void) x17;
                    {
                        lua_Unsigned x18 /* ui */ = ((lua_Unsigned)x17) - 1;
                        const TValue * x19 /* arrslot */ = &x1->array[x18];
                        Table * x20 = hvalue(x19);
                        Table * x21 /* p */ = x20;
                        lua_Unsigned x22 /* ui */ = ((lua_Unsigned)1) - 1;
                        if (PALLENE_UNLIKELY(x22 >= x21->sizearray)) {
                            pallene_renormalize_array(L, x21, x22, 14);
                        }
                        const TValue * x23 /* arrslot */ = &x21->array[x22];
                        lua_Number x24 = fltvalue(x23);
                        lua_Number x25 = x6 + x24;
                        x6 = x25;
                        lua_Unsigned x26 /* ui */ = ((lua_Unsigned)2) - 1;
                        if (PALLENE_UNLIKELY(x26 >= x21->sizearray)) {
                            pallene_renormalize_array(L, x21, x26, 15);
                        }
                        const TValue * x27 /* arrslot */ = &x21->array[x26];
                        lua_Number x28 = fltvalue(x27);
                        lua_Number x29 = x7 + x28;
                        x7 = x29;
                    }
                    x14 = intop(+, x14, x16);
                }
            }
            x10 = intop(+, x10, x12);
        }
        luaC_condGC(L, {
            StackValue* x30 = L->top;
            sethvalue(L, s2v(x30), x1); x30++;
            L->top = x30;
        }, {
            L->top -= 1;
        });
        Table * x31 = luaH_new(L);
        luaH_resizearray(L, x31, 2);
        TValue * x32 = x31->array;
        lua_Number x33 = (lua_Number) x9;
        lua_Number x34 = x6 / x33;
        setfltvalue(x32 + 0, x34);
        lua_Number x35 = (lua_Number) x9;
        lua_Number x36 = x7 / x35;
        setfltvalue(x32 + 1, x36);
        return x31;
    }
}

static int function_centroid_lua(lua_State *L)
{
    lua_checkstack(L, 1);
    CClosure * x1 = clCvalue(s2v(L->ci->func));
    Udata * x2 /* upvalue table */ = uvalue(&x1->upvalue[0]);
    UValue * x3 /* upvalue array */ = x2->uv;
    (void)x3;
    StackValue* x4 = L->ci->func;
    Table * x8 = hvalue(s2v(x4 + 1));
    lua_Integer x9 = ivalue(s2v(x4 + 2));
    Table * x10 /* ret */ = function_centroid_pallene(L, x8, x9);
    sethvalue(L, s2v(L->top), x10);
    api_incr_top(L);
    return 1;
}

int luaopen_benchmarks_centroid_nocheck(lua_State *L)
{
    lua_checkstack(L, 4);
    /* Allocate upvalue table */
    /* ---------------------- */
    Udata * x1 = luaS_newudata(L, 0, 5);
    UValue * x2 = x1->uv;
    /* Initialize upvalues */
    /* ------------------- */
    TString * x3 = luaS_new(L, "__index");
    setsvalue(L,  &x2[0].uv , x3);
    if (isblack(obj2gco(x1)) && iswhite(obj2gco(x3))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    TString * x4 = luaS_new(L, "__newindex");
    setsvalue(L,  &x2[1].uv , x4);
    if (isblack(obj2gco(x1)) && iswhite(obj2gco(x4))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    TString * x5 = luaS_new(L, "__metatable");
    setsvalue(L,  &x2[2].uv , x5);
    if (isblack(obj2gco(x1)) && iswhite(obj2gco(x5))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    /* new */
    CClosure* x6 = luaF_newCclosure(L, 1);
    x6->f = function_new_lua;
    setuvalue(L, &x6->upvalue[0], x1);
    TValue x7; setclCvalue(L, &x7, x6);
    setobj(L,  &x2[3].uv , &x7);
    if (iscollectable(&x7) && isblack(obj2gco(x1)) && iswhite(gcvalue(&x7))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    /* centroid */
    CClosure* x8 = luaF_newCclosure(L, 1);
    x8->f = function_centroid_lua;
    setuvalue(L, &x8->upvalue[0], x1);
    TValue x9; setclCvalue(L, &x9, x8);
    setobj(L,  &x2[4].uv , &x9);
    if (iscollectable(&x9) && isblack(obj2gco(x1)) && iswhite(gcvalue(&x9))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    /* Create exports table */
    /* -------------------- */
    StackValue* x10 = L->top;
    setuvalue(L, s2v(x10), x1); x10++;
    L->top = x10;
    lua_createtable(L, 0, 2);
    lua_pushstring(L, "new");
    setobj(L, s2v(L->top),  &x2[3].uv ); api_incr_top(L);
    lua_settable(L, -3);
    lua_pushstring(L, "centroid");
    setobj(L, s2v(L->top),  &x2[4].uv ); api_incr_top(L);
    lua_settable(L, -3);
    return 1;
}

