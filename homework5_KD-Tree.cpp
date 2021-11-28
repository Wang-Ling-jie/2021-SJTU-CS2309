#include <iostream>
#include <string>

using namespace std;

struct Item {
    int key[2];
    int value;
    Item(int Key[2],int Value){
        key[0]=Key[0];
        key[1]=Key[1];
        value=Value;
    }
    Item(const Item &item){
        key[0]=item.key[0];
        key[1]=item.key[1];
        value=item.value;
    }
};

class Node {
public:
    Node *left, *right;
    Item item;
    
    Node(Item _item): item(_item), left(NULL), right(NULL) {
    }
};

class Node {
public:
    Node *left, *right;
    Item item;
    
    Node(Item _item): item(_item), left(NULL), right(NULL) {
    }
};

void insert(Node *&root, Item item, int dim) {
    if(root==NULL) {
        root=new Node(item);
        return;
    }
    if(item.key[0]==root->item.key[0]&&item.key[1]==root->item.key[1]) 
        return;        //equal in all dimensions
    if(item.key[dim]<root->item.key[dim])  
        insert(root->left,item,(dim+1)%2);
    if(item.key[dim]>root->item.key[dim])
        insert(root->right,item,(dim+1)%2);
}

// If the queried key doesn't exist, return NULL.
Node *search(Node *root, int key[2], int dim) {
    if(root==NULL) return NULL;
    if(key[0]==root->item.key[0]&&key[1]==root->item.key[1]) return root;
    if(key[dim]<root->item.key[dim])  return search(root->left,key,(dim+1)%2);
    if(key[dim]>root->item.key[dim])  return search(root->right,key,(dim+1)%2); 
    return NULL;
}

// Find the minimum value in a dimension(dimCmp)
Node *findMin(Node *root, int dimCmp, int dim) {
    if(!root) return NULL;
    Node*min=NULL;
    //min为左右子树中dimCmp维度上的最小值
    Node *leftMin=findMin(root->left,dimCmp,(dim+1)%2);
    Node* rightMin=findMin(root->right,dimCmp,(dim+1)%2);
    if(leftMin!=NULL&&rightMin!=NULL) min=(leftMin->item.key[dimCmp]<rightMin->item.key[dimCmp])?leftMin:rightMin;
    else if(leftMin==NULL&&rightMin==NULL) min=NULL;
    else if(leftMin!=NULL&&rightMin==NULL) min=leftMin;
    else if(leftMin==NULL&&rightMin!=NULL) min=rightMin;

    if(min==NULL) return root;
    else  return (min->item.key[dimCmp]<root->item.key[dimCmp])?min:root;
}

// Find the minimum value in a dimension(dimCmp)
Node *findMax(Node *root, int dimCmp, int dim) {
    if(!root) return NULL;
    Node*max=NULL;
    //min为左右子树中dimCmp维度上的最小值
    Node *leftMax=findMax(root->left,dimCmp,(dim+1)%2);
    Node* rightMax=findMax(root->right,dimCmp,(dim+1)%2);
    if(leftMax!=NULL&&rightMax!=NULL) max=(leftMax->item.key[dimCmp]>rightMax->item.key[dimCmp])?leftMax:rightMax;
    else if(leftMax==NULL&&rightMax==NULL) max=NULL;
    else if(leftMax!=NULL&&rightMax==NULL) max=leftMax;
    else if(leftMax==NULL&&rightMax!=NULL) max=rightMax;

    if(max==NULL) return root;
    else  return (max->item.key[dimCmp]>root->item.key[dimCmp])?max:root;
}

void remove(Node *&root, int key[2], int dim) {
    if(root==NULL) return;
    else if(key[dim]<root->item.key[dim]) remove(root->left,key,(dim+1)%2);
    else if(key[dim]>root->item.key[dim]) remove(root->right,key,(dim+1)%2);
    else if(key[0]==root->item.key[0]&&key[1]==root->item.key[1]){
        if(root->left==NULL&&root->right==NULL) {
            delete root;
            root=NULL;
            return;
        }
        if(root->right!=NULL){
            Node*tmp=findMin(root->right,dim,(dim+1)%2);
            root->item.key[0]=tmp->item.key[0];
            root->item.key[1]=tmp->item.key[1];
            root->item.value=tmp->item.value;
            remove(root->right,root->item.key,(dim+1)%2);
        }
        else if(root->left!=NULL){
            Node*tmp=findMax(root->left,dim,(dim+1)%2);
            root->item.key[0]=tmp->item.key[0];
            root->item.key[1]=tmp->item.key[1];
            root->item.value=tmp->item.value;
            remove(root->left,root->item.key,(dim+1)%2);
        }
    }
}

// searchRange contains 4 values [x_min, x_max, y_min, y_max]
// Our test program will call this function with dim=0 treeRange={-9999, 9999, -9999, 9999}
int rangeSearch(Node *root, int dim, int searchRange[4], int treeRange[4]) {
    if(root==NULL) return 0;
    if(root->item.key[0]>=searchRange[0]&&root->item.key[0]<=searchRange[1]&&root->item.key[1]>=searchRange[2]&&root->item.key[1]<=searchRange[3])
        return (rangeSearch(root->left,(dim+1)%2,searchRange,treeRange)+rangeSearch(root->right,(dim+1)%2,searchRange,treeRange)+1);
    else return(rangeSearch(root->left,(dim+1)%2,searchRange,treeRange)+rangeSearch(root->right,(dim+1)%2,searchRange,treeRange));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Node*root=NULL;
    int arr[2],range[4],treeRange[4]={-9999,9999,-9999,9999};
    int num,value,dim;
    string operation;
    cin>>num;
    for(int i=0;i<num;i++){
        cin>>operation;
        if(operation=="insert"){
            cin>>arr[0]>>arr[1]>>value;
            insert(root,{arr,value},0);
        }
        else if(operation=="findMin"){
            cin>>dim;
            cout<<findMin(root,dim,0)->item.key[dim]<<endl;
        }
        else if(operation=="rangeSearch"){
            cin>>range[0]>>range[1]>>range[2]>>range[3];
            cout<<rangeSearch(root,0,range,treeRange)<<endl;
        }
        else if(operation=="remove"){
            cin>>arr[0]>>arr[1];
            remove(root,arr,0);
        }
        else if(operation=="search"){
            cin>>arr[0]>>arr[1];
            if(search(root,arr,0)!=NULL)
                cout<<search(root,arr,0)->item.value<<endl;
            else cout<<"NULL"<<endl;
        }
    }
}

/*
1000
insert -2 -726 0
insert -282 -602 1
insert 836 -828 2
insert 699 -28 3
insert -562 -310 4
insert 20 168 5
insert 181 -873 6
insert 442 814 7
insert -283 -111 8
insert -574 425 9
insert -269 -973 10
insert 841 400 11
insert -885 -525 12
insert -841 -453 13
insert 980 969 14
insert -711 813 15
insert -462 392 16
insert -223 -8 17
insert 883 606 18
insert -856 463 19
insert -416 -749 20
insert 88 604 21
insert -256 374 22
insert 576 576 23
insert 319 -518 24
insert -808 -167 25
insert -65 -247 26
insert -76 -976 27
insert 727 -790 28
insert 488 260 29
insert 489 119 30
insert -700 -218 31
insert -3 -257 32
insert -58 268 33
insert 430 867 34
insert -803 490 35
insert 290 966 36
insert -97 339 37
insert 272 -479 38
insert 975 -398 39
insert 238 -921 40
insert 6 -844 41
insert -137 -662 42
insert 714 -903 43
insert 847 602 44
insert 283 652 45
insert 578 455 46
insert -650 -199 47
insert 281 -711 48
insert 368 660 49
insert -792 171 50
insert 503 -106 51
insert 838 898 52
insert 359 622 53
insert -669 -95 54
insert -532 595 55
insert 944 851 56
insert -86 -311 57
insert -159 647 58
insert 588 181 59
insert 31 -685 60
insert 428 -319 61
insert -943 92 62
insert 93 -508 63
insert 737 -997 64
insert 413 732 65
insert 37 -264 66
insert 346 888 67
insert 651 518 68
insert -109 211 69
insert -965 412 70
insert -563 -818 71
insert 34 -107 72
insert 736 -569 73
insert 529 -536 74
insert -301 -936 75
insert -421 -807 76
insert -655 -951 77
insert 546 720 78
insert 32 -237 79
insert -535 -420 80
insert 961 -196 81
insert 769 165 82
insert -264 -551 83
insert 169 190 84
insert -859 -298 85
insert -465 483 86
insert 62 -274 87
insert -846 224 88
insert -883 712 89
insert -371 -456 90
insert 411 552 91
insert 82 -494 92
insert 539 821 93
insert -268 927 94
insert -174 592 95
insert -171 197 96
insert 866 997 97
insert -756 273 98
insert -177 333 99
insert -170 199 100
insert 518 993 101
insert 117 319 102
insert 315 746 103
insert 668 296 104
insert -599 -355 105
insert -24 798 106
insert 462 856 107
insert 948 736 108
insert 620 234 109
insert 672 723 110
insert -455 442 111
insert 551 202 112
insert 41 415 113
insert 608 -7 114
insert 367 499 115
insert 749 -100 116
insert -294 167 117
insert -342 -560 118
insert 64 -999 119
insert 72 314 120
insert 218 748 121
insert -598 471 122
insert 968 -388 123
insert -167 -657 124
insert -866 -173 125
insert -512 -20 126
insert 352 -521 127
insert -362 -630 128
insert 514 131 129
insert -665 -454 130
insert -169 -529 131
insert 40 -93 132
insert 671 695 133
insert 834 946 134
insert -23 272 135
insert -146 882 136
insert 358 -819 137
insert -646 366 138
insert -561 677 139
insert 154 -718 140
insert -354 918 141
insert 67 363 142
insert 153 -382 143
insert 818 -792 144
insert -333 -182 145
insert -771 -513 146
insert -1000 142 147
insert -22 661 148
insert 705 -651 149
insert -549 -222 150
insert 340 -881 151
insert -487 -652 152
insert -731 688 153
insert 708 -962 154
insert 313 924 155
insert 138 -142 156
insert -194 -502 157
insert -976 546 158
insert 951 -397 159
insert -28 545 160
insert -277 -41 161
insert 85 540 162
insert 832 870 163
insert 469 -716 164
insert 390 -149 165
insert 125 -812 166
insert 685 -677 167
insert 477 913 168
insert 211 -729 169
insert 851 -300 170
insert 938 -902 171
insert 532 642 172
insert 935 -846 173
insert 623 -428 174
insert -781 854 175
insert 869 6 176
insert 622 884 177
insert 176 -217 178
insert 443 362 179
insert 341 -309 180
insert -431 783 181
insert 691 807 182
insert 201 -912 183
insert -355 -220 184
insert -40 174 185
insert -414 986 186
insert 625 706 187
insert 53 -586 188
insert 457 79 189
insert -262 -519 190
insert -393 -891 191
insert 979 -620 192
insert -647 -394 193
insert -558 711 194
insert -816 -211 195
insert 258 -91 196
insert 592 -183 197
insert -486 -451 198
insert -438 563 199
insert 2 517 200
insert 91 -52 201
insert -704 -361 202
insert 63 -637 203
insert 959 81 204
insert -245 109 205
insert -736 492 206
insert -630 -969 207
insert -909 751 208
insert 859 -185 209
insert -967 -851 210
insert -864 -75 211
insert -37 388 212
insert -557 4 213
insert -228 411 214
insert 80 528 215
insert -572 459 216
insert 700 -803 217
insert 491 674 218
insert -479 857 219
insert 458 252 220
insert 725 -273 221
insert -232 805 222
insert -18 -356 223
insert -325 313 224
insert 374 130 225
insert -825 -768 226
insert 50 361 227
insert -315 767 228
insert -497 108 229
insert 581 -992 230
insert 407 750 231
insert 600 -56 232
insert -453 186 233
insert -922 535 234
insert 345 -266 235
insert -308 34 236
insert -19 519 237
insert 431 921 238
insert 416 -81 239
insert 604 -459 240
insert 230 758 241
insert -513 -941 242
insert -977 487 243
insert -257 -191 244
insert 232 -179 245
insert -81 -617 246
insert 435 796 247
insert -826 21 248
insert 144 161 249
insert 343 -68 250
insert 427 686 251
insert 419 554 252
insert 567 -585 253
insert 521 430 254
insert 21 203 255
insert -474 -629 256
insert 774 -659 257
insert 807 -108 258
insert 484 -19 259
insert -1 27 260
insert 985 -693 261
insert 912 729 262
insert -882 -787 263
insert 633 221 264
insert 540 391 265
insert 220 992 266
insert 466 -197 267
insert 937 -253 268
insert -635 -135 269
insert 649 561 270
insert 710 -194 271
insert 973 -876 272
insert 331 629 273
insert 4 869 274
insert 563 -205 275
insert 740 31 276
insert -938 878 277
insert 557 823 278
insert -181 354 279
insert -782 -444 280
insert -43 646 281
insert -624 -761 282
insert 624 510 283
insert 76 862 284
insert -252 -607 285
insert 115 -193 286
insert 122 -603 287
insert 554 938 288
insert 531 912 289
insert 994 915 290
insert -594 -751 291
insert 693 -166 292
insert -92 -35 293
insert 849 690 294
insert 479 773 295
insert 19 98 296
insert 45 900 297
insert 541 -357 298
insert -791 486 299
insert -559 -58 300
insert -397 275 301
insert -602 396 302
insert 306 467 303
insert -473 950 304
insert 616 -293 305
insert -801 -345 306
insert -236 -798 307
insert 158 -552 308
insert -175 -919 309
insert -307 995 310
insert 750 387 311
insert 369 421 312
insert -192 -953 313
insert -653 69 314
insert -877 10 315
insert -894 880 316
insert -997 200 317
insert -548 477 318
insert -90 -535 319
insert 598 -593 320
insert -125 -561 321
insert -463 -6 322
insert -116 608 323
insert 960 -741 324
insert 675 -285 325
insert 822 -640 326
insert 245 -929 327
insert 785 -907 328
insert 583 698 329
insert 640 -589 330
insert 316 290 331
insert -409 -462 332
insert -188 338 333
insert 252 -449 334
insert 12 979 335
insert -609 -543 336
insert -923 -25 337
insert 632 -118 338
insert -404 -461 339
insert -780 285 340
insert 237 543 341
insert -142 844 342
insert -921 -616 343
insert 662 689 344
insert 964 -231 345
insert -38 -833 346
insert 197 -701 347
insert -400 -859 348
insert 291 678 349
insert 854 586 350
insert -578 -664 351
insert -618 -317 352
insert 185 542 353
insert 15 808 354
insert -687 -544 355
insert 257 -381 356
insert -49 228 357
insert 762 -767 358
insert -971 316 359
insert 73 133 360
insert 103 -489 361
insert -224 458 362
insert -520 84 363
insert -29 568 364
insert 522 838 365
insert -642 -413 366
insert 96 -914 367
insert 61 -408 368
insert -593 512 369
insert 548 232 370
insert -738 619 371
insert -787 670 372
insert 105 59 373
insert -501 547 374
insert 974 955 375
insert -141 326 376
insert 336 -576 377
insert 629 -305 378
insert 318 916 379
insert -383 -606 380
insert -953 93 381
insert 128 -605 382
insert 957 -742 383
insert -263 643 384
insert 140 -814 385
insert -490 149 386
insert -426 996 387
insert 48 -813 388
insert 800 258 389
insert 452 911 390
insert -996 909 391
insert 370 72 392
insert 713 432 393
insert -622 -410 394
insert -898 91 395
insert -95 279 396
insert -964 -658 397
insert -701 243 398
insert 920 904 399
insert 804 320 400
search -953 93
search 168 821
insert -784 654 401
search 201 -912
search -883 712
search -421 -807
search 61 -408
search 762 -767
search -646 366
rangeSearch 171 603 358 686
rangeSearch -536 -234 -327 -233
insert -932 -407 402
insert -768 868 403
insert -68 439 404
insert -919 960 405
search 954 911
findMin 1
search 608 -7
insert -424 -472 406
rangeSearch -985 -739 -716 -325
insert 385 -558 407
findMin 0
insert -477 322 408
search -520 84
search -362 -630
rangeSearch 982 1291 809 1211
insert -79 -424 409
findMin 1
remove 140 -814
search -784 654
rangeSearch -611 -439 699 1006
search -174 592
findMin 0
search 283 652
search -474 -629
rangeSearch 356 382 -583 -535
search -333 -182
search 103 -489
search -923 -32
rangeSearch -184 287 309 459
insert 499 702 410
search -252 -607
search 964 -231
remove 416 -81
search 700 -803
search 201 -912
rangeSearch -790 -740 -778 -405
search 4 869
rangeSearch 348 543 -928 -735
insert -507 342 411
search 979 -620
remove -19 519
insert -237 842 412
search 623 -428
search -462 392
search 44 420
rangeSearch -588 -195 -674 -210
search -125 -561
remove -92 -35
findMin 0
findMin 0
rangeSearch 825 1007 -766 -384
search 588 181
insert 123 -571 413
insert -128 -346 414
rangeSearch -568 -340 -654 -235
insert 397 -550 415
rangeSearch 442 807 -559 -209
findMin 0
remove -371 -456
remove -404 -461
search 144 161
remove -791 486
findMin 1
findMin 1
rangeSearch -738 -603 -460 -384
rangeSearch -958 -926 22 137
search -618 -317
findMin 1
findMin 1
search -455 442
search 428 -319
rangeSearch 713 841 -490 -337
search 841 400
findMin 0
insert 129 -30 416
remove -578 -664
search -782 -444
search -932 -407
search 299 903
search 407 750
rangeSearch 298 545 -597 -364
rangeSearch 617 871 -262 4
remove 63 -637
rangeSearch 935 1204 975 1343
search -894 880
insert 116 -169 417
search -655 -951
search 974 955
rangeSearch -666 -176 -181 -157
search 749 -100
rangeSearch -291 -165 455 550
rangeSearch -908 -804 -432 -76
search -738 619
search 272 -479
rangeSearch 504 699 -353 -343
search -602 396
search -308 34
remove 290 966
rangeSearch -223 -69 916 1345
search -465 483
rangeSearch -943 -492 309 623
findMin 1
insert -34 443 418
search 105 59
insert 597 -27 419
search -473 950
insert -712 756 420
remove 624 510
rangeSearch 593 749 -902 -417
search -18 -356
search 469 -716
remove 514 131
rangeSearch -947 -455 -124 58
search -192 -953
rangeSearch 305 649 850 1226
search -23 272
insert 586 -740 421
search -486 -451
findMin 0
insert 304 -546 422
search 529 -536
remove 4 869
rangeSearch 96 446 -245 -85
remove 499 702
search 258 -91
remove 431 921
search 975 -398
search 2 517
insert -202 50 423
search -445 -567
search 576 576
rangeSearch -250 28 -643 -560
insert -907 12 424
insert 956 -260 425
insert 842 593 426
search 725 -273
insert 198 -845 427
search -216 793
search -177 333
search -909 751
search -549 -222
findMin 1
insert 26 908 428
insert -752 697 429
rangeSearch -899 -702 -187 280
insert 321 -854 430
search -782 -444
findMin 0
search 211 -729
search 834 946
rangeSearch 434 707 -619 -219
search 814 -688
search 428 -319
search -19 549
remove -473 950
findMin 1
insert 821 745 431
rangeSearch -937 -466 -479 -251
findMin 1
search -40 174
search 50 361
search 822 -640
search 319 -518
search -965 412
remove 442 814
search 973 -876
search 245 -929
rangeSearch -774 -604 -245 119
findMin 1
findMin 1
search 563 -205
insert -719 -153 432
search 34 -107
search 368 660
search -971 316
insert 781 -517 433
rangeSearch -77 364 447 662
remove -34 443
remove 714 -903
rangeSearch 112 281 -297 -96
findMin 1
search -273 401
rangeSearch -484 -369 476 809
search 257 -381
search -91 -471
rangeSearch 626 780 640 795
insert -944 -993 434
search 864 600
rangeSearch 239 529 -649 -168
findMin 0
search -282 -602
rangeSearch 685 782 -934 -901
search 369 421
insert -688 769 435
insert -809 -90 436
insert -344 -396 437
findMin 1
rangeSearch 214 677 902 1075
insert -884 -384 438
insert -834 409 439
rangeSearch -70 182 478 730
insert -190 596 440
search -624 -761
search -711 813
search 957 -742
rangeSearch 340 578 492 744
insert -459 743 441
findMin 0
rangeSearch -930 -849 -836 -703
search 737 -997
insert -774 58 442
rangeSearch -551 -363 627 679
search -40 174
rangeSearch -942 -778 227 244
remove -731 688
search -771 -513
rangeSearch 156 582 668 710
search 750 387
search 713 432
search 917 -997
search 503 -106
remove -76 -976
rangeSearch -327 1 578 872
remove 128 -605
rangeSearch -893 -540 -885 -572
findMin 0
rangeSearch -275 216 364 787
findMin 0
insert 74 935 443
remove -856 463
rangeSearch -928 -532 -718 -439
search -114 150
remove 138 -142
rangeSearch 292 698 -156 150
search -801 -345
insert -906 -281 444
rangeSearch -362 -253 527 646
search -971 316
search -557 4
remove 705 -651
search -137 -662
search 553 723
findMin 1
search 428 -602
rangeSearch 260 308 -910 -815
findMin 0
search -976 546
search 279 -632
insert 701 132 445
insert -415 840 446
search 616 -293
search 968 -388
search 681 26
search 737 -997
findMin 1
remove -687 -544
findMin 1
remove -354 918
rangeSearch -727 -578 841 1113
insert 277 182 447
rangeSearch 660 1130 639 785
rangeSearch 526 784 50 289
search 452 911
insert 738 -37 448
search 693 -166
remove -557 4
findMin 0
insert -693 501 449
search -477 322
insert -694 446 450
insert -850 -764 451
rangeSearch 212 505 -996 -972
rangeSearch 908 1042 -863 -613
insert -827 -898 452
search 346 888
search -364 -380
remove 957 -742
search -416 -749
remove -416 -749
search 620 234
findMin 1
search -393 -891
rangeSearch 735 772 453 845
rangeSearch -970 -473 -779 -685
rangeSearch -419 -131 -829 -407
insert -581 -895 453
search -965 412
search 105 59
search 960 -741
rangeSearch -944 -831 -235 -15
insert -537 292 454
rangeSearch -351 -108 -1 291
remove -65 -247
findMin 0
findMin 0
rangeSearch 66 202 770 1103
search -921 -616
search 557 823
search -631 731
findMin 1
insert 648 -495 455
search -446 -5
insert 856 -725 456
findMin 1
search -43 646
remove 53 -586
search -342 -560
rangeSearch 779 1111 -764 -572
rangeSearch 611 627 719 770
rangeSearch 563 1018 917 1143
search 198 -845
insert -892 509 457
search 105 59
rangeSearch -482 -328 514 887
rangeSearch -842 -427 107 191
rangeSearch -46 -13 276 625
insert -428 71 458
insert -297 -822 459
search -128 -346
search 793 -775
search 141 -295
search 608 -7
insert -998 703 460
insert 811 377 461
remove 50 361
findMin 1
remove 331 629
search -719 -153
insert 666 -279 462
remove 851 -300
search -413 -920
search 241 -546
insert 767 932 463
insert -179 -497 464
findMin 1
rangeSearch 258 723 -433 56
insert -652 804 465
findMin 0
search -174 592
search -232 805
search 93 556
search -622 -410
search 615 107
search -532 595
search 491 674
search 64 -999
search 197 -701
remove -146 882
search 951 -397
search 45 900
remove 633 221
insert -66 104 466
search -712 756
search 489 119
rangeSearch 478 924 -348 75
search -307 995
insert -914 448 467
search 352 -521
insert 997 975 468
search 842 593
insert 716 983 469
rangeSearch 510 610 -769 -476
search -159 647
findMin 0
search -412 -520
remove -23 272
rangeSearch 685 828 -919 -862
search 489 119
search 974 955
findMin 0
search -190 596
rangeSearch 641 676 175 564
search -669 -95
rangeSearch -245 -124 330 366
insert 865 954 470
insert 168 172 471
insert -91 434 472
rangeSearch 946 1293 680 993
search 352 -521
findMin 0
findMin 1
search 489 119
rangeSearch 196 555 -883 -847
search 76 862
insert -475 120 473
search -501 547
search 693 -166
rangeSearch 117 461 -925 -750
findMin 1
rangeSearch 962 1375 33 195
search -424 -472
search -264 -551
search 407 750
search -414 986
search 31 -685
insert 99 -838 474
rangeSearch 638 824 865 1004
search 202 478
insert 412 650 475
findMin 1
findMin 1
findMin 0
insert -525 873 476
remove 912 729
search -655 -314
search -257 -191
insert 309 694 477
insert -107 183 478
remove 620 234
findMin 1
search 260 239
findMin 0
search 849 690
rangeSearch -600 -399 364 674
search -188 338
search -908 -435
search 158 -552
rangeSearch 144 521 -683 -204
search 776 316
rangeSearch -856 -435 -834 -606
rangeSearch 554 738 680 988
search 315 746
search -28 545
insert 826 580 479
search 37 -264
search 984 169
findMin 1
remove 74 935
search 727 -790
rangeSearch -731 -444 -761 -463
rangeSearch 597 733 -600 -184
findMin 0
rangeSearch 730 1063 -343 -83
insert 195 152 480
rangeSearch 746 782 -54 222
rangeSearch 134 525 421 828
insert -721 539 481
search -846 224
rangeSearch -963 -716 -614 -235
findMin 0
search 522 838
insert 754 -667 482
findMin 1
search 640 -589
insert 795 988 483
rangeSearch -860 -782 418 648
insert -199 -132 484
rangeSearch -626 -156 -876 -458
search 304 -546
search -177 333
search 581 -444
findMin 0
search -650 -199
search -465 483
insert 922 -872 485
rangeSearch 872 1360 -446 -258
search -38 -833
rangeSearch 674 891 -571 -276
search 632 -118
search -784 654
search -177 333
findMin 0
search -400 -859
insert -695 -70 486
search -474 -629
findMin 0
search -688 769
rangeSearch 496 704 -729 -301
remove 834 946
search -431 783
insert -13 -826 487
search 469 -716
rangeSearch 513 940 -616 -190
search -561 677
rangeSearch -130 268 143 621
rangeSearch 325 720 -183 174
insert 678 775 488
remove 522 838
rangeSearch 769 1134 -652 -196
insert 879 788 489
search -711 813
remove 935 -846
insert -903 559 490
findMin 0
search -657 738
rangeSearch 645 831 -931 -474
insert 448 -739 491
insert 467 -950 492
rangeSearch 184 302 493 939
insert -233 846 493
search 973 -876
insert 867 456 494
insert 722 -215 495
remove 176 -217
findMin 0
search 230 758
remove 867 456
search 281 -711
search -325 313
rangeSearch 764 977 -842 -479
search -294 167
search 488 260
search 838 898
insert 353 753 496
insert 850 -753 497
findMin 0
search 600 -56
rangeSearch 41 356 -685 -656
insert -158 -934 498
rangeSearch 953 1316 208 259
insert -811 931 499
search 211 -729
rangeSearch -411 -40 -608 -453
search 666 -279
rangeSearch -573 -322 -299 -95
search -652 804
findMin 1
search 306 467
findMin 1
rangeSearch 982 1104 316 346
search 666 -279
remove 345 -266
insert 146 734 500
findMin 1
findMin 1
insert 885 -324 501
findMin 1
findMin 1
rangeSearch -145 -94 -183 301
findMin 0
search -771 -513
search 822 -640
insert -863 -350 502
insert -625 -730 503
insert 717 -506 504
search -194 -502
search 283 652
search 714 -569
findMin 0
search -137 -662
insert 824 956 505
search 856 -725
insert 454 -913 506
remove -738 619
remove 491 674
findMin 1
search -906 -281
insert 653 -650 507
search -877 10
search -125 -561
search 866 -313
rangeSearch -545 -362 674 991
rangeSearch -772 -678 -802 -525
search -898 91
rangeSearch -348 -186 931 1242
remove -809 -90
search -12 174
remove -669 -95
rangeSearch 117 178 905 1038
rangeSearch -365 -210 -111 275
rangeSearch -999 -566 251 498
search 37 -264
insert -955 687 508
search -455 442
search -97 339
rangeSearch 268 577 720 1001
insert 376 607 509
rangeSearch 603 982 -811 -676
rangeSearch 910 1393 807 822
remove 232 -179
insert 812 -419 510
search 922 -872
insert -407 151 511
rangeSearch -57 304 -186 -176
search -593 512
rangeSearch 465 955 -191 -97
findMin 1
insert -899 902 512
findMin 0
insert -156 57 513
rangeSearch 470 491 -518 -168
rangeSearch 225 349 796 1018
insert -311 -216 514
remove -642 -413
search 563 -205
insert -566 664 515
remove 959 81
search -179 -497
*/