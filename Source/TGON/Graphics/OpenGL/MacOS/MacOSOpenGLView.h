/**
 * @filename    MacOSOpenGLView.h
 * @author      ggomdyu
 * @since       09/18/2017
 * @brief
 */

#pragma once
#import <AppKit/NSOpenGLView.h>

@interface MacOSOpenGLView : NSOpenGLView
{
}

- (id)initWithDisplayLink;
@end
