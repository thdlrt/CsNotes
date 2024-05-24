## Spring-Bash与数据处理

#### 数据下载

- 从提供的云盘链接（https://box.nju.edu.cn/d/3e125ec5ca2f476db822/）下载商品元数据和评论数据。

#### 定义数据模型

定义User、Product和Review三类对象，并设置关联关系。

```java
@Entity
public class User {
    @Id
    private String userId;
    private String profileName;
    // Getters and Setters
}

@Entity
public class Product {
    @Id
    private String productId;
    private String mainCategory;
    private String title;
    private Double averageRating;
    private Integer ratingNumber;
    private String description;
    private String features;
    private String price;
    private String store;
    private String categories;
    private String details;
    // Getters and Setters
}

@Entity
public class Review {
    @Id
    private String reviewId;
    private Double rating;
    private String title;
    private String text;
    private String translatedText;
    private String asin;
    private String parentAsin;
    private String userId;
    private Long timestamp;
    private Integer helpfulVote;
    private Boolean verifiedPurchase;
    // Getters and Setters
}

```

#### **配置Spring Batch**

创建Spring Batch配置，读取JSONL文件，将数据转换为对象，并保存到数据库。

```java
@Configuration
@EnableBatchProcessing
public class BatchConfig {
    @Autowired
    private JobRepository jobRepository;

    @Autowired
    private PlatformTransactionManager transactionManager;

    @Autowired
    private DataSource dataSource;

    @Bean
    public Job importJob() {
        return new JobBuilder("importJob", jobRepository)
                .incrementer(new RunIdIncrementer())
                .start(step1())
                .next(step2())
                .build();
    }

    @Bean
    public Step step1() {
        return new StepBuilder("step1", jobRepository)
                .<Product, Product>chunk(10, transactionManager)
                .reader(productItemReader())
                .processor(productItemProcessor())
                .writer(productItemWriter())
                .build();
    }

    @Bean
    public Step step2() {
        return new StepBuilder("step2", jobRepository)
                .<Review, Review>chunk(10, transactionManager)
                .reader(reviewItemReader())
                .processor(reviewItemProcessor())
                .writer(reviewItemWriter())
                .build();
    }
    
    // Define ItemReader, ItemProcessor, ItemWriter for Product and Review
    ...
}

```

#### 数据高级处理

##### 图片URL验证

在ProductItemProcessor中处理数据转换，进行图片的URL验证。

尝试通过http获取图片，如果URL无效，将其设为null。

```java
@Component
public class ProductItemProcessor implements ItemProcessor<Product, Product> {

    @Override
    public Product process(Product product) throws Exception {
        for (ProductImage image : product.getImages()) {
            if (!isValidURL(image.getLarge())) {
                image.setLarge(null); // 如果URL无效，将其设为null
            }
        }
        return product;
    }

    private boolean isValidURL(String url) {
        try (CloseableHttpClient httpClient = HttpClients.createDefault()) {
            HttpHead request = new HttpHead(url);
            HttpResponse response = httpClient.execute(request);
            return response.getStatusLine().getStatusCode() == 200;
        } catch (IOException e) {
            return false;
        }
    }
}
```

##### 评论的翻译

这里使用谷歌翻译的API实现

这部分通过在ReviewItemProcessor中对数据进行处理实现

```java
private final Translate translate;

    public ReviewItemProcessor() {
        translate = TranslateOptions.getDefaultInstance().getService();
    }

    @Override
    public Review process(Review review) throws Exception {
        // 翻译评论文本
        Translation translation = translate.translate(
                review.getText(),
                Translate.TranslateOption.sourceLanguage("en"),
                Translate.TranslateOption.targetLanguage("zh")
        );
        review.setText(translation.getTranslatedText());

        // 验证图片URL
        for (ReviewImage image : review.getImages()) {
            if (!isValidURL(image.getLargeImageUrl())) {
                image.setLargeImageUrl(null); // 如果URL无效，将其设为null或进行其他处理
            }
        }
        return review;
    }
```

#### h2数据库中数据展示

![image-20240524132837953](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524132837953.png)

![image-20240524132854099](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524132854099.png)

![image-20240524132912017](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524132912017.png)

## POS机的修改

> 由于对前端不太熟悉，发现原先的图片路径计算方式不适用于网络图片，但是没能成功解决图片的显示问题

首先对存储层、服务层以及原先的数据model进行修改，实现对接到新的数据库

![image-20240524140817459](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524140817459.png)

- 扩展现有的ProductService和ProductController，添加获取产品评论的功能，并创建新的API

```java
@RestController
@RequestMapping("/productsService")
public class ProductController implements ProductsServiceApi {
    @Autowired
    private ProductService posService;

    @GetMapping("/products/{productId}/details")
    @CrossOrigin(value = "*", maxAge = 1800, allowedHeaders = "*")
    public ResponseEntity<ProductDetailsDto> showProductDetailsById(@PathVariable String productId) {
        Product product = posService.getProduct(productId);
        if (product == null) {
            return ResponseEntity.notFound().build();
        }
        List<Review> reviews = posService.getProductReviews(productId);
        ProductDetailsDto productDetailsDto = new ProductDetailsDto();
        productDetailsDto.setProduct(productMapper.toProductDto(product));
        productDetailsDto.setReviews(reviews);
        return ResponseEntity.ok(productDetailsDto);
    }
}
```

- 点击商品后的评论展示界面

![image-20240524141205352](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524141205352.png)