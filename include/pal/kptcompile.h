/******************************************************************************
 *
 * Copyright 2011 KeyPoint Technologies (UK) Ltd.   
 * All rights reserved. This program and the accompanying materials   
 * are made available under the terms of the Eclipse Public License v1.0  
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html

 *           
 * Contributors: 
 * KeyPoint Technologies (UK) Ltd - Initial API and implementation
 *
 *****************************************************************************/
 /**
 * @file    kptcompile.h
 *
 * @brief   General platform independent defines used in the compilation.
 *
 * @details
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTCOMPILE_H
#define H_KPTCOMPILE_H

/** Defines an integer using the bit associated with a category. */
#define KPTCAT(aBitIndex)       (1 << (aBitIndex))

#define KPTCAT_NONE             0           /**< Empty Category */
#define KPTCAT_ALL              0xFFFFFFFF  /**< All categories */
#define KPTCAT_ERROR            KPTCAT(0)   /**< Error Category */
#define KPTCAT_WARNING          KPTCAT(1)   /**< Warning Category */
#define KPTCAT_INFORMATION      KPTCAT(2)   /**< Information Category */
#define KPTCAT_DEBUG            KPTCAT(3)   /**< Debug Category */
#define KPTCAT_PERFORMANCE      KPTCAT(4)   /**< Performance Category */
#define KPTCAT_ALGORITHM        KPTCAT(5)   /**< Algorithm Category */
#define KPTCAT_RESERVED6	    KPTCAT(6)   /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED7        KPTCAT(7)   /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED8        KPTCAT(8)   /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED9        KPTCAT(9)   /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED10       KPTCAT(10)  /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED11       KPTCAT(11)  /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED12       KPTCAT(12)  /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED13       KPTCAT(13)  /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED14       KPTCAT(14)  /**< Reserved for KPT libraries */
#define KPTCAT_RESERVED15       KPTCAT(15)  /**< Reserved for KPT libraries */

#define KPTCAT_APP01            KPTCAT(16)  /**< Application category */
#define KPTCAT_APP02            KPTCAT(17)  /**< Application category */
#define KPTCAT_APP03            KPTCAT(18)  /**< Application category */
#define KPTCAT_APP04            KPTCAT(19)  /**< Application category */
#define KPTCAT_APP05            KPTCAT(20)  /**< Application category */
#define KPTCAT_APP06            KPTCAT(21)  /**< Application category */
#define KPTCAT_APP07            KPTCAT(22)  /**< Application category */
#define KPTCAT_APP08            KPTCAT(23)  /**< Application category */
#define KPTCAT_APP09            KPTCAT(24)  /**< Application category */
#define KPTCAT_APP10            KPTCAT(25)  /**< Application category */
#define KPTCAT_APP11            KPTCAT(26)  /**< Application category */
#define KPTCAT_APP12            KPTCAT(27)  /**< Application category */
#define KPTCAT_APP13            KPTCAT(28)  /**< Application category */
#define KPTCAT_APP14            KPTCAT(29)  /**< Application category */
#define KPTCAT_APP15            KPTCAT(30)  /**< Application category */
#define KPTCAT_APP16            KPTCAT(31)  /**< Application category */

/** Macro to check if a category is defined in a group value */
#define KPTCAT_ISDEFINED(aGroup, aCategory) (0 != ((aGroup) & (aCategory)))

#endif /* #ifndef H_KPTCOMPILE_H */
