<!-- language-all: lang-html -->

_This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world_

By Gabriel Staples  
First Written: 7 Sept. 2020

**See my original answer online on Stack Overflow here: https://stackoverflow.com/questions/12090472/github-readme-md-center-image/62383408#62383408.**


**TLDR:**  
Just jump straight down to look at the 3 examples (1.1, 1.2, and 1.3) in the section below called **"1. Centering and aligning images _in GitHub readmes_ using the deprecated HTML `align` attribute"**!

**Full answer:** 


# Background on how to center and align images in markdown:

So, it turns out that **GitHub explicitly blocks/filters out _all attempts at editing any form of CSS styles (including [external, internal, and inline](https://www.w3schools.com/css/css_howto.asp))_ inside GitHub `*.md` markdown files, such as readmes.** See here: 

1. https://stackoverflow.com/questions/51956361/custom-css-file-for-readme-md-in-a-github-repo/51956450#51956450

    > GitHub does not allow for CSS to affect README.md files through CSS for security reasons...

1. https://github.community/t/github-flavored-markdown-doesnt-render-css-styles-inside-a-html-block/126258/2?u=electricrcaircraftguy

    > Unfortunately you cannot use CSS in GitHub markdown as it is a part of the sanitization process.
    > 
    > > The HTML is sanitized, aggressively removing things that could harm you and your kin—such as `script` tags, inline-styles, and `class` or `id` attributes.
    > 
    > source: https://github.com/github/markup

**So, that means to center or align images _in GitHub readmes_, your only solution is to use the [deprecated HTML `align` attribute](https://www.w3.org/TR/html4/present/graphics.html#h-15.1.2) (that happens to still function), as [this answer](https://stackoverflow.com/a/12118349/4561887) shows.** 

I should also point out that although that solution does indeed work, it is causing a lot of confusion for that answer to claim to use `inline css to solve the problem`, since, like @Poikilos points out in the comments, that answer has no CSS in it whatsoever. Rather, the `align="center"` part of the `<p>` element is a [deprecated HTML attribute](https://www.w3.org/TR/html4/present/graphics.html#h-15.1.2) (that happens to still function) and is NOT CSS. All CSS, whether [external, internal, or inline](https://www.w3schools.com/css/css_howto.asp) is banned from GitHub readmes and explicitly removed, as indicated through trial-and-error and in the two references above.

This leads me to split my answer into two answers here: 

1. "Centering and aligning images in GitHub readmes using the deprecated HTML `align` attribute", and
1. "Centering and aligning images using modern CSS in any markdown document where you also have control over CSS styles".

Option 2 only works in places where you have full control over CSS styles, such as in a custom [GitHub Pages](https://pages.github.com/) website you make maybe?

----


# 1. Centering and aligning images _in GitHub readmes_ using the deprecated HTML `align` attribute:

This works in any GitHub `*.md` markdown file, such as a GitHub `readme.md` file. It relies on the deprecated HTML `align` attribute, but still works fine. You can see a full demo of this in an actual GitHub readme in my eRCaGuy_hello_world repo here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/markdown/github_readme_center_and_align_images.md.

Notes:

1. _Be sure to set `width="100%"` inside each of your `<p>` paragraph elements below, or else the entire paragraph tries to allow word wrap around it, causing weird and less-predicable effects._
1. To resize your image, simly set `width="30%"`, or whatever percent you'd like between 0% and 100%, to get the desired effect! This is _much_ easier than trying to set a pixel size, such as `width="200" height="150"`, as using a `width` percent automatically adjusts to your viewer's screen and to the page display width, and it automatically resizes the image as you resize your browser window as well. It also avoids skewing the image into unnatural proportions. It's a great feature!
1. Options for the [(deprecated) HTML `align` attribute](https://www.w3.org/TR/html4/present/graphics.html#h-15.1.2) include `left`, `center`, `right`, and `justify`.


## 1.1. Align images left, right, or centered, with NO WORD WRAP:

This:

```html
**Align left:**
<p align="left" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align center:**
<p align="center" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align right:**
<p align="right" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>
```

Produces this:

**Align left:**
<p align="left" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align center:**
<p align="center" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align right:**
<p align="right" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

If you'd like to set the text itself to left, center, or right, you can include the text inside the `<p>` element as well, as regular HTML, like this:

```html
<p align="right" width="100%">
    This text is also aligned to the right.<br>
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>
```

To produce this:

<p align="right" width="100%">
    This text is also aligned to the right.<br>
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>


## 1.2. Align images left, right, or centered, WITH word wrap:

This:

```html
**Align left (works fine):**

<img align="left" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.


**Align center (doesn't really work):**

<img align="center" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.


**Align right (works fine):**

<img align="right" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.
```

Produces this:

**Align left (works fine):**

<img align="left" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.


**Align center (doesn't really work):**

<img align="center" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.


**Align right (works fine):**

<img align="right" width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 

[Arduino](https://en.wikipedia.org/wiki/Arduino) (/ɑːrˈdwiːnoʊ/) is an open-source hardware and software company, project and user community that designs and manufactures single-board microcontrollers and microcontroller kits for building digital devices. Its hardware products are licensed under a CC-BY-SA license, while software is licensed under the GNU Lesser General Public License (LGPL) or the GNU General Public License (GPL),[1] permitting the manufacture of Arduino boards and software distribution by anyone. Arduino boards are available commercially from the official website or through authorized distributors. Arduino board designs use a variety of microprocessors and controllers. The boards are equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards ('shields') or breadboards (for prototyping) and other circuits.


## 1.3. Align images side-by-side:

_Reminder: MAKE SURE TO GIVE THE entire `<p>` paragraph element the full 100% column width (`width="100%"`, as shown below) or else text gets word-wrapped around it, botching your vertical alignment and vertical spacing/formatting you may be trying to maintain!_


This:

```html
33% width each (_possibly_ a little too wide to fit all 3 images side-by-side, depending on your markdown viewer):
<p align="center" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

32% width each (perfect size to just barely fit all 3 images side-by-side):
<p align="center" width="100%">
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

31% width each:
<p align="center" width="100%">
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

30% width each:
<p align="center" width="100%">
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>
```

Produces this:

33% width each (_possibly_ a little too wide to fit all 3 images side-by-side, depending on your markdown viewer):
<p align="center" width="100%">
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="33%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

32% width each (perfect size to just barely fit all 3 images side-by-side):
<p align="center" width="100%">
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="32%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

31% width each:
<p align="center" width="100%">
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="31%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

30% width each:
<p align="center" width="100%">
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="30%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

I am aligning all paragraph `<p>` elements above to the `center`, but you can also align `left` or `right`, as shown in previous examples, to force the row of images to get aligned that way too. Example:

This:

```html
Align the whole row of images to the right this time:
<p align="right" width="100%">
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>
```

Produces this (aligning the whole row of images according to the `align` attribute set above, or to the _right_ in this case). Generally, `center` is preferred, as done in the examples above.

Align the whole row of images to the right this time:
<p align="right" width="100%">
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="25%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>


----

# 2. Centering and aligning images using modern CSS in any markdown document where you also have control over CSS styles:

This works in any markdown file, such as a [GitHub Pages](https://pages.github.com/) website maybe?, where you do have full control over CSS styles. This does NOT work in any GitHub `*.md` markdown file, such as a `readme.md`, therefore, because GitHub expliclty scans for and disables all custom CSS styling you attempt to use. See above.

## TLDR;

Use this HTML/CSS to add and center an image and set its size to 60% of the screen space width inside your markdown file, which is usually a good starting value:

    <img src="https://i.stack.imgur.com/RJj4x.png" 
         style="display:block;float:none;margin-left:auto;margin-right:auto;width:60%"> 

Change the `width` CSS value to whatever percent you want, or remove it altogether to use the markdown default size, which I think is 100% of the screen width if the image is larger than the screen, or it is the actual image width otherwise.

Done! 

Or, keep reading for a lot more information.

## Here are various HTML and CSS options which work perfectly inside markdown files, so long as CSS is not explicitly forbidden:

## 1. Center and configure (resize) ALL images in your markdown file:

Just copy and paste this to the top of your markdown file to center and resize all images in the file (then just insert any images you want with normal markdown syntax):

    <style>
    img
    {
        display:block; 
        float:none; 
        margin-left:auto;
        margin-right:auto;
        width:60%;
    }
    </style> 

Or, here is the same code as above but with detailed HTML and CSS comments to explain exactly what is going on:

    <!-- (This is an HTML comment). Copy and paste this entire HTML `<style>...</style>` element (block)
    to the top of your markdown file -->
    <style>
    /* (This is a CSS comment). The below `img` style sets the default CSS styling for all images
    hereafter in this markdown file. */
    img
    {
        /* Default display value is `inline-block`. Set it to `block` to prevent surrounding text from
        wrapping around the image. Instead, `block` format will force the text to be above or below the
        image, but never to the sides. */
        display:block; 
        /* Common float options are `left`, `right`, and `none`. Set to `none` to override any previous
        settings which might have been `left` or `right`. `left` causes the image to be to the left,
        with text wrapped to the right of the image, and `right` causes the image to be to the right,
        with text wrapped to its left, so long as `display:inline-block` is also used. */
        float:none; 
        /* Set both the left and right margins to `auto` to cause the image to be centered. */
        margin-left:auto;
        margin-right:auto;
        /* You may also set the size of the image, in percent of width of the screen on which the image
        is being viewed, for example. A good starting point is 60%. It will auto-scale and auto-size
        the image no matter what screen or device it is being viewed on, maintaining proporptions and 
        not distorting it. */
        width:60%;
        /* You may optionally force a fixed size, or intentionally skew/distort an image by also 
        setting the height. Values for `width` and `height` are commonly set in either percent (%) 
        or pixels (px). Ex: `width:100%;` or `height:600px;`. */
        /* height:400px; */
    }
    </style> 

Now, whether you insert an image using markdown:

    ![](https://i.stack.imgur.com/RJj4x.png)

Or HTML in your markdown file:

    <img src="https://i.stack.imgur.com/RJj4x.png"> 

...it will be automatically centered and sized to 60% of the screenview width, as described in the comments within the HTML and CSS above. _(Of course the 60% size is really easily changeable too, and I present simple ways below to do it on an image-by-image basis as well)._ 

## 2. Center and configure images on a case-by-case basis, one at a time:

Whether or not you have copied and pasted the above `<style>` block into the top of your markdown file, this will also work, as it overrides and takes precedence over any file-scope style settings you may have set above:

    <img src="https://i.stack.imgur.com/RJj4x.png" style="display:block;float:none;margin-left:auto;margin-right:auto;width:60%"> 

You can also format it on multiple lines, like this, and it will still work:

    <img src="https://i.stack.imgur.com/RJj4x.png" 
         alt="this is an optional description of the image to help the blind and show up in case the 
              image won't load" 
         style="display:block; /* override the default display setting of `inline-block` */ 
                float:none; /* override any prior settings of `left` or `right` */ 
                /* set both the left and right margins to `auto` to center the image */
                margin-left:auto; 
                margin-right:auto;
                width:60%; /* optionally resize the image to a screen percentage width if you want too */
                "> 

## 3. In addition to all of the above, you can also create CSS style _classes_ to help stylize individual images:

Add this whole thing to the top of your markdown file. 

    <style>

    /* By default, make all images center-aligned, and 60% of the width 
    of the screen in size */
    img
    {
        display:block; 
        float:none; 
        margin-left:auto;
        margin-right:auto;
        width:60%;
    }

    /* Create a CSS class to style images to left-align, or "float left" */
    .leftAlign
    {
        display:inline-block;
        float:left;
        /* provide a 15 pixel gap between the image and the text to its right */
        margin-right:15px; 
    }

    /* Create a CSS class to style images to right-align, or "float right" */
    .rightAlign
    {
        display:inline-block;
        float:right;
        /* provide a 15 pixel gap between the image and the text to its left */
        margin-left:15px;
    }

    </style> 

Now, your `img` CSS block has set the default setting for images to be centered and 60% of the width of the screen space in size, but you can use the `leftAlign` and `rightAlign` CSS classes to override those settings on an image-by-image basis. 

For example, this image will be **center-aligned and 60% in size** (the default I set above):

    <img src="https://i.stack.imgur.com/RJj4x.png"> 

This image will be **left-aligned**, however, with text wrapping to its right, using the `leftAlign` CSS class we just created above!

    <img src="https://i.stack.imgur.com/RJj4x.png" class="leftAlign">

It might look like this:

[![enter image description here][1]][1]

You can still **override any of its CSS properties via the `style` attribute**, however, such as width, like this:

    <img src="https://i.stack.imgur.com/RJj4x.png" class="leftAlign" style="width:20%">

And now you'll get this:

[![enter image description here][2]][2]

## 4. Create 3 CSS classes, but don't change the `img` markdown defaults

Another option to what we just showed above, where we modified the default `img` `property:value` settings and created 2 classes, is to just leave all the default markdown `img` properties alone, but create 3 custom CSS classes, like this:

    <style>

    /* Create a CSS class to style images to center-align */
    .centerAlign
    {
        display:block;
        float:none;
        /* Set both the left and right margins to `auto` to cause the image to be centered. */
        margin-left:auto;
        margin-right:auto;
        width:60%;
    }

    /* Create a CSS class to style images to left-align, or "float left" */
    .leftAlign
    {
        display:inline-block;
        float:left;
        /* provide a 15 pixel gap between the image and the text to its right */
        margin-right:15px; 
        width:60%;
    }

    /* Create a CSS class to style images to right-align, or "float right" */
    .rightAlign
    {
        display:inline-block;
        float:right;
        /* provide a 15 pixel gap between the image and the text to its left */
        margin-left:15px;
        width:60%;
    }

    </style> 

Use them, of course, like this:

    <img src="https://i.stack.imgur.com/RJj4x.png" class="centerAlign" style="width:20%">

Notice how I manually set the `width` property using the CSS `style` attribute above, but if I had something more complicated I wanted to do, I could also create some additional classes like this, adding them inside the `<style>...</style>` block above:

    /* custom CSS class to set a predefined "small" size for an image */
    .small
    {
        width:20%;
        /* set any other properties, as desired, inside this class too */
    }

Now you can assign multiple classes to the same object, like this. Simply [separate class names by a space, NOT a comma][3]. In the event of conflicting settings, I believe whichever setting comes *last* will be the one that takes effect, overriding any previously-set settings. This should also be the case in the event you set the same CSS properties multiple times in the same CSS class or inside the same HTML `style` attribute. 

    <img src="https://i.stack.imgur.com/RJj4x.png" class="centerAlign small">

## 5. Consolidate Common Settings in CSS Classes:

The last trick is one I learned in this answer here: https://stackoverflow.com/questions/27697549/how-can-i-use-css-to-style-multiple-images-differently/27701152#27701152. As you can see above, all 3 of the CSS `align` classes set the image width to 60%. Therefore, this common setting can be set all at once like this if you wish, then you can set the specific settings for each class afterwards:

    <style>

    /* set common properties for multiple CSS classes all at once */
    .centerAlign, .leftAlign, .rightAlign {
        width:60%;
    }

    /* Now set the specific properties for each class individually */

    /* Create a CSS class to style images to center-align */
    .centerAlign
    {
        display:block;
        float:none;
        /* Set both the left and right margins to `auto` to cause the image to be centered. */
        margin-left:auto;
        margin-right:auto;
    }

    /* Create a CSS class to style images to left-align, or "float left" */
    .leftAlign
    {
        display:inline-block;
        float:left;
        /* provide a 15 pixel gap between the image and the text to its right */
        margin-right:15px; 
    }

    /* Create a CSS class to style images to right-align, or "float right" */
    .rightAlign
    {
        display:inline-block;
        float:right;
        /* provide a 15 pixel gap between the image and the text to its left */
        margin-left:15px;
    }

    /* custom CSS class to set a predefined "small" size for an image */
    .small
    {
        width:20%;
        /* set any other properties, as desired, inside this class too */
    }

    </style> 

----

# More Details:

## 1. My thoughts on HTML and CSS in Markdown

As far as I'm concerned, anything which can be written in a markdown document and get the desired result is all we are after, not some "pure markdown" syntax. 

In C and C++, the compiler compiles down to assembly code, and the assembly is then assembled down to binary. Sometimes, however, you need the low-level control that only assembly can provide, and so you can write inline assembly right inside of a C or C++ source file. Assembly is the "lower level" language and it can be written right inside C and C++. 

So it is with markdown. Markdown is the high-level language which is interpreted down to HTML and CSS. However, where we need extra control, we can just "inline" the lower-level HTML and CSS right inside of our markdown file, and it will still be interpreted correctly. In a sense, therefore, HTML and CSS _are_ valid "markdown" syntax. 

So, to center an image in markdown, use HTML and CSS.

## 2. Standard image insertion in markdown:

How to add a basic image in markdown with default "behind-the-scenes" HTML and CSS formatting:

This markdown:

    ![](https://i.stack.imgur.com/RJj4x.png)

Will produce this output:

![](https://i.stack.imgur.com/RJj4x.png)

This is [my fire-shooting hexacopter I made](https://www.electricrcaircraftguy.com/2016/05/battlebots-season-2-buzz-fire-drone.html). 

You can also optionally add a description in the opening square brackets. Honestly I'm not even sure what that does, but perhaps it gets converted into an [HTML `<img>` element `alt` attribute][4], which gets displayed in case the image can't load, and may be read by screen readers for the blind. So, this markdown:

    ![this is my hexacopter I built](https://i.stack.imgur.com/RJj4x.png)

will also produce this output:

![this is my hexacopter I built](https://i.stack.imgur.com/RJj4x.png)


## 3. More details on what's happening in the HTML/CSS when centering and resizing an image in markdown:

Centering the image in markdown requires that we use the extra control that HTML and CSS can give us directly. You can insert and center an individual image like this:

    <img src="https://i.stack.imgur.com/RJj4x.png" 
         alt="this is my hexacopter I built" 
         style="display:block; 
                float:none; 
                margin-left:auto; 
                margin-right:auto;
                "> 

Here's more info. on what is going on here:

1. The `<img` part of the above code is the HTML "**start tag**", while the `>` at the end is the HTML "**end tag**". 
1. Everything from the start tag to the end tag, inclusive, makes up this HTML `img` "**element**". 
1. HTML `img` **"tags"/"elements"** are used to insert images into HTML. 
1. Each of the assignments inside the element is configuring an HTML "**attribute**". 
1. The **"style" attribute** accepts **CSS styling**, so everything inside the double quotes here: `style=""` is a CSS `property:value` key-value "**declaration**". 
    1. Note that each CSS "property:value declaration" is separated by a semicolon (`;`), whereas each HTML "attribute" in this "element" is separated by a space (` `). 
1. To get the image to center in our HTML and CSS code above, the key "attributes" are simply the `src` and `style` ones. 
1. The `alt` one is optional. 
1. Inside the HTML `style` attribute, which accepts CSS styling, the key declarations are all 4 that I show: `display:block`, `float:none`, `margin-left:auto`, and `margin-right:auto`. 
    1. If nothing has previously set the `float` **property** before, then you can leave off this declaration, but it's a good idea to have it anyway just in case. 
    1. If first learned how to center an image using HTML and CSS here: https://www.w3schools.com/howto/howto_css_image_center.asp.
1. CSS uses C-style comments (`/* my comment */`).


# References:
1. Read more about CSS Syntax here: https://www.w3schools.com/css/css_syntax.asp
1. Read about ["HTML Tags vs Elements" here][5].
1. I did a lot of my HTML and CSS styling practice in my GitHub markdown readme here: https://github.com/ElectricRCAircraftGuy/Arduino-STEM-Presentation
1. I learned just about everything I know about HTML and CSS by clicking around on w3schools.com. Here's a few specific pages:
    1. %%%%%**https://www.w3schools.com/howto/howto_css_image_center.asp**
    1. https://www.w3schools.com/css/css_float.asp
        1. https://www.w3schools.com/css/tryit.asp?filename=trycss_layout_float2
    1. https://www.w3schools.com/css/css3_images.asp
    1. https://www.w3schools.com/tags/default.asp
    1. HTML and CSS comments: https://www.w3schools.com/css/css_comments.asp
1. My fire-shooting hexacopter I made: https://www.electricrcaircraftguy.com/2016/05/battlebots-season-2-buzz-fire-drone.html


  [1]: https://i.stack.imgur.com/jaU2j.png
  [2]: https://i.stack.imgur.com/uS5FK.png
  [3]: https://www.ironpaper.com/webintel/articles/assign-two-css-classes-together-for-one-object/#:~:text=It%20is%20possible%20to%20assign,box%20for%20images%2C%20for%20example.&text=We%20used%20color%20coding%20of,space%20(not%20a%20comma).
  [4]: https://www.w3schools.com/tags/att_img_alt.asp
  [5]: https://www.tutorialrepublic.com/html-tutorial/html-elements.php#:~:text=HTML%20Tags%20Vs%20Elements,see%20in%20the%20above%20illustration.